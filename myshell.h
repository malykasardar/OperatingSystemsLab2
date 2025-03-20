#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <libgen.h>
#include <unistd.h>

// Function declarations
void change_directory(char *path);
void list_directory(char *path);
void list_environment();
void echo_comment(char *comment);
void pause_shell();
void execute_external_command(char *input);
void execute_command(char *input);

#endif
