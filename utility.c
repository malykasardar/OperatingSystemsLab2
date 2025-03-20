#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void change_directory(char *path) {
    if (path == NULL) {
        // Print current directory if no path is provided
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("getcwd");
        }
    } else {
        // Change directory to the specified path
        if (chdir(path) != 0) {
            perror("myshell");
        }
    }
}

void list_directory(char *path) {
    if (path == NULL) {
        path = "."; // Default to current directory
    }

    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

void list_environment() {
    extern char **environ;
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

void echo_comment(char *comment) {
    if (comment != NULL) {
        printf("%s\n", comment);
    }
}

void pause_shell() {
    printf("Press Enter to continue...");
    getchar(); // Wait for Enter key
}
