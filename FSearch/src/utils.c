#include "utils.h"

//function to concatenate the formatted user prompt to fit into the URL with a '+' instead of spaces
char *concatenate(char **searchQuery, int n){

    char *newQuery = malloc(MAX_QUERY_LENGTH * sizeof(char));
    if (!newQuery) return NULL;

    size_t remaining = MAX_QUERY_LENGTH - 1; //-1 for the space for '\0'

    newQuery[0] = '\0';

    if(n > 2){
        //I start from 1 because the first argument is the program name
        for(size_t i = 1; i < n && remaining > 0; ++i){

            size_t len = strlen(searchQuery[i]);
            if(len > remaining)
                len = remaining;

            strncat(newQuery, searchQuery[i], len);
            remaining -= len;

            if(remaining > 0 && i < n-1){
                strncat(newQuery, "+", 2); //2 spaces to make space for '\0' added by strncat
                --remaining;
            }

            if(remaining == 0 && i < n-1){
                puts("\nPrompt too long! Prompt accepted:");
                puts(newQuery);
                break;
            }
        }

        
    }
    else{
        if(strlen(searchQuery[1]) > remaining){
            strncat(newQuery, searchQuery[1], remaining);

            puts("\nPrompt troppo lungo! Prompt accettato:");
            puts(newQuery);
        }
        else
            strcat(newQuery, searchQuery[1]);
    }

    return newQuery;
}


char *getHomePath(){
    char *home = getenv("HOME");

    if (home == NULL) {
        fprintf(stderr, "User's HOME directory not found!\n");
        exit(1);
    }
    else
        return home;
}

//function to find the path of the FSearch/ program directory
int find_fsearch(const char *dir, char *found_path){
    DIR *dp = opendir(dir);
    if (!dp) return 0;
    struct dirent *entry;
    struct stat st;
    char path[MAX_PATH];

    while ((entry = readdir(dp)) != NULL){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
        if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)){
            if (strcmp(entry->d_name, "FSearch") == 0){
                strncpy(found_path, path, MAX_PATH);
                closedir(dp);
                return 1;
            }
            if (find_fsearch(path, found_path)){
                closedir(dp);
                return 1;
            }
        }
    }
    closedir(dp);
    return 0;
}
/*
int find_fsearch(const char *dir, char *found_path){
    DIR *dp = opendir(dir);
    if (dp == NULL) return 0;

    struct dirent *entry;
    struct stat st;
    char path[MAX_PATH];

    while ((entry = readdir(dp)) != NULL) {
        // Ignore . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
        if (stat(path, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                //If it's the FSearch folder, I copy the path and return 1
                if (strcmp(entry->d_name, "FSearch") == 0) {
                    strncpy(found_path, path, MAX_PATH);
                    closedir(dp);
                    return 1;
                }
                //Otherwise recursion into the subfolder
                if (find_fsearch(path, found_path)) {
                    closedir(dp);
                    return 1;
                }
            }
        }
    }
    closedir(dp);
    return 0;  // not found
}
*/