# MyShell User Manual

## Internal Commands
- `cd <directory>`: Change the current directory.
- `clr`: Clear the screen.
- `dir <directory>`: List the contents of a directory.
- `environ`: List all environment variables.
- `echo <comment>`: Display a comment.
- `help`: Display this user manual.
- `pause`: Pause the shell until 'Enter' is pressed.
- `quit`: Quit the shell.

## External Commands
All other commands are treated as external commands and executed using `execvp`.

## Batch Mode
To run the shell in batch mode, provide a file containing commands as an argument:
```bash
./myshell commands.txt


## Group 1
Done by:
- Abdullah Hanoosh, Student ID: 100749026
- Malyka Sardar, Student ID: 100752640
- Marwan Alam, Student ID: 100842087
- Vidurshan Sribalasuhabiramam, Student ID: 100558257
