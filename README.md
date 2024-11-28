# AutoClicker

## Overview

**AutoClicker** is a console-based autoclicker program written in C++ using multithreading and condition variables. It simulates mouse clicks at a user-defined interval and provides a user-friendly interface to control its functionality in real time.

---

## Features

- **Enable/Disable Autoclicker**: Use `X` to enable and `Z` to disable the autoclicker.
- **Adjust Click Speed**: Use `+` to increase and `-` to decrease the click speed.
- **Quit Program**: Use `Q` to terminate the program gracefully.
- **Live Status Display**: Provides a real-time display of the current status and speed.
- **Thread-Safe Execution**: Uses multithreading and condition variables for responsive input handling and click simulation.

---

## How It Works

1. **Multithreading**:
   - **Clicker Thread**: Executes simulated mouse clicks at the specified interval.
   - **Input Thread**: Listens for user inputs (`X`, `Z`, `+`, `-`, `Q`) and updates the state.
   - **Display thread**: Programme status and instructions are continuously displayed in the console.

2. **Controls**:
   - **'X' Key**: Activates the autoclicker.
   - **'Z' Key**: Deactivates the autoclicker.
   - **'+' Key**: Increases click speed (decreases interval).
   - **'-' Key**: Decreases click speed (increases interval).
   - **'Q' Key**: Exits the program.

3. **Click Simulation**:
   - Uses the `mouse_event` function to generate left-click events.

---

## Requirements

### Software
- Windows OS (for `mouse_event` and `GetAsyncKeyState` APIs).
- C++ compiler with support for C++11 or later (e.g., GCC, MSVC).

### Libraries
- `<iostream>`: For console input and output.
- `<thread>`: For multithreading.
- `<atomic>`: For thread-safe boolean and integer operations.
- `<Windows.h>`: For Windows-specific APIs.
- `<condition_variable>`: For thread synchronization.

---

## How to Build and Run

1. **Clone the Repository**:
   ```bash
   git clone <https://github.com/nineslop/Autoclicker>
   cd <repository-folder>
   ```

2. **Build the Program**:
   Use a C++ compiler, e.g., MSVC or MinGW:
   ```bash
   g++ -o AutoClicker AutoClicker.cpp -std=c++11 -lpthread
   ```

3. **Run the Executable**:
   ```bash
   ./AutoClicker
   ```

---

## Usage Instructions

1. Launch the program.
2. Follow the on-screen menu for instructions:
   - Press `X` to enable the autoclicker.
   - Press `Z` to disable the autoclicker.
   - Use `+` and `-` to adjust the click speed (default is 10ms).
   - Press `Q` to quit the program.
3. Observe live updates in the console about the current state and click interval.

---

## Key Highlights

- **Robust Console Interface**: Displays a logo, status, and menu dynamically.
- **Thread Safety**: Synchronizes state changes using `std::atomic` and `std::condition_variable`.
- **Customizable**: Modify the `clickInterval` logic to fine-tune the speed limits.

---

## Notes and Limitations

- The program relies on the Windows API and may not work on non-Windows systems.
- Ensure sufficient permissions to access the console and simulate mouse events.
- Adjust the `Sleep` durations in the input handler for more or less responsive input handling.

---

## Author

Developed as a utility for controlled mouse automation with an interactive console-based interface.

Feel free to contribute, report issues, or suggest improvements!
