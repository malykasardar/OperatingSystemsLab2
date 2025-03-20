
/*
 * Group 1
 * Done by:
 * - Abdullah Hanoosh, Student ID: 100749026
 * - Malyka Sardar, Student ID: 100752640
 * - Marwan Alam, Student ID: 100842087
 * - Vidurshan Sribalasuhabiramam, Student ID: 100558257
 */






#include "myshell.h"

void execute_command(char *input) {
    char *token;
    char *delim = " \n";
    token = strtok(input, delim);

    if (token != NULL) {
        if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, delim);
            if (token == NULL || strcmp(token, "~") == 0) token = getenv("HOME");
            change_directory(token);
        } else if (strcmp(token, "clr") == 0) {
            printf("\033[H\033[J");
        } else if (strcmp(token, "dir") == 0) {
            token = strtok(NULL, delim);
            list_directory(token ? token : ".");
        } else if (strcmp(token, "mkdir") == 0) {
            token = strtok(NULL, delim);
            if (token != NULL) make_directory(token);
            else fprintf(stderr, "mkdir: missing operand\n");
        } else if (strcmp(token, "rmdir") == 0) {
            token = strtok(NULL, delim);
            if (token != NULL) remove_directory(token);
            else fprintf(stderr, "rmdir: missing operand\n");
        } else if (strcmp(token, "environ") == 0) {
            list_environment();
        } else if (strcmp(token, "echo") == 0) {
            token = strtok(NULL, "");
            echo_comment(token ? token : "\n");
        } else if (strcmp(token, "help") == 0) {
            char command[1024];
            snprintf(command, sizeof(command), "cat README.md");
            system(command);
        } else if (strcmp(token, "pause") == 0) {
            pause_shell();
        } else if (strcmp(token, "quit") == 0) {
            exit(0);
        } else {
            execute_external_command(input);
        }
    }
}

void execute_external_command(char *input) {
    char *args[64];
    int i = 0;
    args[i] = strtok(input, " \n");
    while (args[i] != NULL) args[++i] = strtok(NULL, " \n");
    args[i] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
    }
}

int main(int argc, char *argv[]) {
    char input[1024];
    while (1) {
        printf("MyShell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        if (input[strlen(input) - 1] == '\n') input[strlen(input) - 1] = '\0';
        execute_command(input);
    }
    return 0;
}

