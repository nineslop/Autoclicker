#include <iostream>
#include <thread>
#include <atomic>
#include <Windows.h>
#include <condition_variable>

using namespace std;

void menu()
{
    cout << "Press 'X' to enable and 'Z' to disable autoclicker\n";
    cout << "Press 'Q' to quit the program\n";
    cout << "Press '+' to increase click speed\n";
    cout << "Press '-' to decrease click speed\n";
}

class AutoClicker
{
public:
    AutoClicker()
        : running(true), click(false), clickInterval(10)
    {
        clickerThread = std::thread(&AutoClicker::clicker, this);
        inputThread = std::thread(&AutoClicker::inputHandler, this);
        displayThread = std::thread(&AutoClicker::displayStatus, this);
    }

    ~AutoClicker()
    {
        running = false;
        cv.notify_all();
        if (clickerThread.joinable()) clickerThread.join();
        if (inputThread.joinable()) inputThread.join();
        if (displayThread.joinable()) displayThread.join();
    }

    void clicker()
    {
        while (running)
        {
            std::unique_lock<std::mutex> lk(cv_m);
            cv.wait(lk, [&] { return click.load() || !running.load(); });

            if (running && click)
            {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Sleep(clickInterval.load());
            }
        }
    }

    void inputHandler()
    {
        while (running)
        {
            if (GetAsyncKeyState('X') & 0x8000)
            {
                click = true;
                cv.notify_all();
                Sleep(200);
            }
            else if (GetAsyncKeyState('Z') & 0x8000)
            {
                click = false;
                Sleep(200);
            }
            else if (GetAsyncKeyState('Q') & 0x8000)
            {
                running = false;
                cv.notify_all();
                break;
            }
            else if (GetAsyncKeyState(VK_OEM_PLUS) & 0x8000)
            {
                increaseClickSpeed();
                Sleep(200);
            }
            else if (GetAsyncKeyState(VK_OEM_MINUS) & 0x8000)
            {
                decreaseClickSpeed();
                Sleep(200);
            }
            Sleep(1);
        }
    }

    void displayStatus()
    {
        while (running)
        {
            clearConsole();
            displayLogo();
            menu();
            cout << "Autoclicker is " << (click ? "enabled" : "disabled") << "\n";
            cout << "Current click speed: " << clickInterval.load() << " ms\n";
            Sleep(500);
        }
    }

    bool isRunning() const
    {
        return running;
    }

private:
    std::atomic<bool> running;
    std::atomic<bool> click;
    std::atomic<int> clickInterval;
    std::condition_variable cv;
    std::mutex cv_m;
    std::thread clickerThread;
    std::thread inputThread;
    std::thread displayThread;

    void increaseClickSpeed()
    {
        clickInterval = max(1, clickInterval.load() - 5);
    }

    void decreaseClickSpeed()
    {
        clickInterval += 5;
    }

    void clearConsole()
    {
        std::cout << "\033[2J\033[1;1H";
    }

    void displayLogo()
    {
        cout << R"(
   _____ __    ________________  ____  _____   ________   ____        _ 
  / ___// /   / ____/ ____/ __ \/ __ \/  _/ | / / ____/  / __/   __  (_)
  \__ \/ /   / __/ / __/ / /_/ / /_/ // //  |/ / / __   / /_| | / / / /
 ___/ / /___/ /___/ /___/ ____/ ____// // /|  / /_/ /_ / __/| |/ / / /
/____/_____/_____/_____/_/   /_/   /___/_/ |_/\____/(_)_/   |___/_/ /
                                                               /___/
)";
    }
};

BOOL WINAPI ConsoleHandler(DWORD signal)
{
    if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT)
    {
        std::cout << "Exiting program...\n";
        return TRUE;
    }
    return FALSE;
}

int main()
{
    if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE))
    {
        std::cerr << "ERROR: The control handler could not be installed\n";
        return 1;
    }

    {
        AutoClicker autoClicker;
        menu();
        std::cout << "Press 'Q' to quit the program\n";
        while (autoClicker.isRunning())
        {
            Sleep(100);
        }
    }

    return 0;
}
