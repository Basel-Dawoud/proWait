# Non-Blocking Wait with Signal Handling

## Overview

This C program demonstrates how to handle child processes asynchronously in the parent process using signal handlers. The program creates multiple child processes that terminate after a specified period, and the parent process handles their termination without blocking, ensuring no zombie processes are left.

The program uses `SIGCHLD` signals and `sigaction()` to handle child termination. When a child terminates, the parent process receives the signal, uses `waitpid()` to reap the child, and reports the child’s termination status.

## Features
- **Asynchronous Child Process Management**: The parent process doesn't block while waiting for child processes to terminate. Instead, it handles child terminations as they occur.
- **Prevention of Zombie Processes**: The program uses `waitpid()` with `WNOHANG` to avoid zombie processes by ensuring the parent process reaps child processes immediately when they terminate.
- **Custom Exit Statuses**: Each child process exits with a unique status, which is reported by the parent process.

## Installation and Usage

To compile and run this program, you'll need a Linux-based system with a C compiler (`gcc`) installed.

### Clone the repository

Clone this repository to your local machine:

```bash
git clone https://github.com/yourusername/non-blocking-wait.git
cd non-blocking-wait
```

### Compile the code

To compile the C code, run the following command:

```bash
gcc -o proWait proWait.c
```

### Run the program

After compilation, run the program using:

```bash
./proWait
```

### Example Output

When the program runs, you will see output indicating how each child process exited:

```bash
Child with PID 12345 exited with status 42
Child with PID 12346 exited with status 43
Child with PID 12347 exited with status 44
...
```

## How It Works

1. **Forking Child Processes**: The program forks 10 child processes, each of which sleeps for 4 seconds before exiting with a custom exit status.
2. **Signal Handling**: The parent process sets up a signal handler using `sigaction()` to catch `SIGCHLD` signals, which are sent when a child process terminates.
3. **Handling Termination**: When a child process terminates, the signal handler (`wait_handler`) is invoked. It uses `waitpid()` to reap the terminated child and report its exit status. This ensures that no child processes remain as zombies.
4. **Simulating Parent Work**: While the parent waits for child processes to terminate, it continues to simulate other work by sleeping for 1 second in a loop.

### Key Concepts:
- **SIGCHLD**: The signal sent to the parent process when a child process terminates.
- **sigaction()**: Used to set up the signal handler for `SIGCHLD`.
- **waitpid()**: Used to reap terminated child processes. The `WNOHANG` option ensures that `waitpid()` does not block the parent process.

## File Structure

- **`proWait.c`**: The C source code for the program implementing the non-blocking wait system call using signals.
- **`README.md`**: The documentation for this project.

## Example Code Walkthrough

### Main Function
- The main function forks 10 child processes.
- Each child process sleeps for 4 seconds and then exits with a custom status.
- The parent process sets up signal handling and then simulates doing other work while waiting for child processes to exit.

### Signal Handling (`sigaction`)
- `sigaction()` is used to install a signal handler for `SIGCHLD`, which is triggered when any child process terminates.
- The signal handler (`wait_handler`) reaps child processes immediately by calling `waitpid()` with the `WNOHANG` option, ensuring no zombie processes.

### `wait_handler` Function
- This function is called when a `SIGCHLD` signal is received.
- It calls `waitpid()` to retrieve the exit status of the terminated child process.
- The function then checks the exit status using macros like `WIFEXITED()`, `WIFSIGNALED()`, and `WIFSTOPPED()` to determine the reason for termination and prints the appropriate message.

## Acknowledgements
- [Linux Signals Documentation](https://man7.org/linux/man-pages/man7/signal.7.html) for signal handling and `sigaction()`.
- [C Programming](https://www.cprogramming.com/) for general C programming resources.
```
Contact

If you have any questions or suggestions, feel free to contact me at:

    Email: baselinux2024@gmail.com
