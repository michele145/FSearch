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
                puts("\nPrompt troppo lungo! Prompt accettato:");
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