#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>


#define MAX_QUERY_LENGTH 1000
#define MAX_PATH 32500       //32727 max path len on windows (on linux is 4096)

char *concatenate(char **searchQuery/* [ n ] */, int n);
char* getHomePath();
int find_fsearch(const char *dir, char *found_path);

#endif