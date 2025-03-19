# MyShell Project
This project implements a simple shell in C, capable of interpreting basic commands, like `cd` to change the working directory.
## Files Included
- `myshell.c`: Contains the core logic for interacting with the user and executing commands.
- `utility.c`: Contains utility functions like `change_directory` for the `cd` command.
- `myshell.h`: Header file that defines the interface for the shell's functions.
- `Makefile`: Used to automate the build process.
- `README.md`: Documentation for the project.
## Compilation and Usage
To compile the shell, run: make
To start the shell, run: ./myshell
## Example Usage
MyShell> cd /tmp # Changes directory to /tmp
MyShell> cd # Prints the current working directory
MyShell> unknown # Prints "Command not recognized."
To clean up compiled files:
$ make clean
