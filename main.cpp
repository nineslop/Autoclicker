#include <iostream>
#include <Windows.h>

using namespace std;

void menu()
{
	cout << "Press 'X' to enable and 'Z' to disable autoclicker\n";
}

void clicker()
{
	bool click = false; 

	while (true)
	{
		if (GetAsyncKeyState('X')) 
		{
			click = true;
		}
		else if (GetAsyncKeyState('Z')) 
		{
			click = false;
		}
		if (click == true) 
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(1); 
		}
	}
}

int main()
{
	menu();
	clicker();

	return 0;
}