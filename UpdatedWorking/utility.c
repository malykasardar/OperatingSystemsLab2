#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void change_directory(char *path) {
    if (chdir(path) != 0) {
        perror("chdir");
    }
}

void list_directory(char *path) {
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
    } else {
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    }
}

void list_environment() {
    extern char **environ;
    for (char **env = environ; *env; env++) {
        printf("%s\n", *env);
    }
}

void echo_comment(char *comment) {
    printf("%s\n", comment);
}

void pause_shell() {
    printf("Press Enter to continue...\n");
    while (getchar() != '\n');
}

void make_directory(char *path) {
    if (mkdir(path, 0777) != 0) {
        perror("mkdir");
    }
}

void remove_directory(char *path) {
    if (rmdir(path) != 0) {
        perror("rmdir");
    }
}

