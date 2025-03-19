/* myshell.c */
#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ; // Environment variables

void execute_command(char *input) {
    char *args[100]; // Command arguments
    char *token;
    char *delim = " \n";
    int i = 0;

    token = strtok(input, delim);
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, delim);
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    // Handle internal commands
    if (strcmp(args[0], "cd") == 0) {
        change_directory(args[1]);
    } else if (strcmp(args[0], "clr") == 0) {
        clear_screen();
    } else if (strcmp(args[0], "dir") == 0) {
        list_directory(args[1]);
    } else if (strcmp(args[0], "environ") == 0) {
        print_environment();
    } else if (strcmp(args[0], "echo") == 0) {
        echo_text(args);
    } else if (strcmp(args[0], "help") == 0) {
        display_help();
    } else if (strcmp(args[0], "pause") == 0) {
        pause_shell();
    } else if (strcmp(args[0], "quit") == 0) {
        exit(0);
    } else {
        execute_external(args);
    }
}

int main(int argc, char *argv[]) {
    char input[1024];
    
    setenv("shell", getcwd(NULL, 0), 1); // Set shell environment variable
    
    if (argc > 1) { // Batch mode
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening batch file");
            return 1;
        }
        while (fgets(input, sizeof(input), file)) {
            printf("%s", input);
            execute_command(input);
        }
        fclose(file);
        return 0;
    }
    
    while (1) {
        printf("MyShell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        execute_command(input);
    }
    return 0;
}
