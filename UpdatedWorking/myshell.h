/*
 * Group 1
 * Done by:
 * - Abdullah Hanoosh, Student ID: 100749026
 * - Malyka Sardar, Student ID: 100752640
 * - Marwan Alam, Student ID: 100842087
 * - Vidurshan Sribalasuhabiramam, Student ID: 100558257
 */




#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void change_directory(char *path);
void list_directory(char *path);
void list_environment();
void echo_comment(char *comment);
void pause_shell();
void execute_external_command(char *input);
void make_directory(char *path);
void remove_directory(char *path);

#endif

