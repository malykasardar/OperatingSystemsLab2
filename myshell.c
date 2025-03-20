#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <libgen.h> // For dirname()
#include <unistd.h> // For readlink()

void execute_command(char *input) {
    char *token;
    char *delim = " \n"; // Split input by spaces and newlines
    token = strtok(input, delim);

    if (token != NULL) {
        if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, delim); // Get the directory path
            change_directory(token);
        } else if (strcmp(token, "clr") == 0) {
            system("clear"); // Clear the screen
        } else if (strcmp(token, "dir") == 0) {
            token = strtok(NULL, delim); // Get the directory path
            list_directory(token);
        } else if (strcmp(token, "environ") == 0) {
            list_environment(); // List all environment variables
        } else if (strcmp(token, "echo") == 0) {
            // Pass the entire input string after "echo"
            char *comment = input + strlen("echo "); // Skip "echo "
            echo_comment(comment);
        } else if (strcmp(token, "help") == 0) {
            // Get the path to the shell executable
            char path[1024];
            ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
            if (len != -1) {
                path[len] = '\0';
                // Get the directory of the executable
                char *dir = dirname(path);
                // Construct the full path to README.md
                char readme_path[2048];
                snprintf(readme_path, sizeof(readme_path), "%s/README.md", dir);
                // Display the user manual using cat
                char command[4096];
                snprintf(command, sizeof(command), "cat %s", readme_path);
                system(command);
            } else {
                perror("readlink");
            }
        } else if (strcmp(token, "pause") == 0) {
            pause_shell(); // Pause the shell
        } else if (strcmp(token, "quit") == 0) {
            exit(0); // Quit the shell
        } else {
            // Handle external commands
            execute_external_command(input);
        }
    }
}

void execute_external_command(char *input) {
    char *args[64];
    int i = 0;

    // Tokenize the input
    char *token = strtok(input, " \n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL; // Null-terminate the argument list

    // Execute the command
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("execvp"); // If execvp fails
        exit(1);
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for the child process to finish
    } else {
        perror("fork"); // Fork failed
    }
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    if (argc > 1) {
        // Batch mode: Read commands from a file
        file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("fopen");
            exit(1);
        }
    }

    char input[1024];
    while (1) {
        if (file == NULL) {
            // Interactive mode: Prompt the user
            printf("MyShell> ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                break; // Exit on EOF
            }
        } else {
            // Batch mode: Read commands from the file
            if (fgets(input, sizeof(input), file) == NULL) {
                break; // Exit on EOF
            }
        }
        execute_command(input); // Process the input
    }

    if (file != NULL) {
        fclose(file); // Close the file in batch mode
    }
    return 0;
}
