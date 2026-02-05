#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"
#include "setupCurlCjson.h"
#include "utils.h"

#define MAX_URL_LENGTH 2048


static void printSearchApi(cJSON*);
static void printAiApi(cJSON*);


int main(int argc, char **argv){

    static void (*printResults)(cJSON*); //function pointer to point to the results printing functions

    if(argc < 2){
        puts("Too few arguments!");
        return 1;
    }


    char queryURL[MAX_URL_LENGTH]; //where put the complete url
    char *query; //both for apiAI and apiSearch, represent the prompt
    query = concatenate(argv, argc);


    //setup for apiAI
    char *aiURL = "https://serpapi.com/search.json?engine=google_ai_mode&q=";
    sprintf(queryURL, "%s%s&google_domain=google.com&hl=en&gl=us&api_key=cb8907c21e9e3f96b27086b34b75595d0663251f50001903637e05fbf8dbe08e",
            aiURL, query);
    char *jsonAiFile = "../json_report/AiReport.json";

    setupCurl(query, queryURL, jsonAiFile);
    cJSON *AiJson = setupJson(jsonAiFile);

    //print apiAI
    printResults = printAiApi;
    printResults(AiJson);
    cJSON_Delete(AiJson);



    puts("---------------------------------------------------------------------------------------------");



    //setup pfor apiSearch
    queryURL[0] = '\0'; //I 'empty' the string for the request url

    char *searchURL = "https://serpapi.com/search.json?engine=google_light&q=";
    sprintf(queryURL, "%s%s&google_domain=google.com&hl=en&gl=us&api_key=cb8907c21e9e3f96b27086b34b75595d0663251f50001903637e05fbf8dbe08e",
            searchURL, query);
    char *jsonSearchFile = "../json_report/searchReport.json";
    
    setupCurl(query, queryURL, jsonSearchFile);

    printf("\nRISULTATI GOOGLE PER:\t");
    puts(*argv);
    puts("\n\n\n\n");

    cJSON *searchJson = setupJson(jsonSearchFile);


    //print api google search
    printResults = printSearchApi;
    printResults(searchJson);
    cJSON_Delete(searchJson);


    
    free(query); //since it was dynamically allocated by the concatenate() function in utils.c
    return 0;
}



static void printSearchApi(cJSON *searchJson){
    if(searchJson != NULL){
        cJSON *links = cJSON_GetObjectItemCaseSensitive(searchJson, "organic_results");
        cJSON *elements = NULL;
        if(!links){
            puts("La ricerca non ha prodotto risultati...");
            return;
        }

        //since I only want the first 5 results I control the loop iterations with 'index'
        short index = 1;
        cJSON_ArrayForEach(elements, links){
            if(index > 5)
                break;

            //extract the link, title and text from the 'organic_results' json array
            cJSON *url = cJSON_GetObjectItemCaseSensitive(elements, "link");
            if(cJSON_IsString(url) && url->valuestring != NULL)
                printf("%s\n", url->valuestring);

            cJSON *title = cJSON_GetObjectItemCaseSensitive(elements, "title");
            if(cJSON_IsString(title) && title->valuestring != NULL)
                printf("TITLE:\n%s\n------------------------------------------\n", title->valuestring);

            cJSON *description = cJSON_GetObjectItemCaseSensitive(elements, "snippet");
            if(cJSON_IsString(description) && description->valuestring != NULL)
                printf("%s\n", description->valuestring);
            
            printf("\n\n\n\n");

            ++index;
        }
    }

}


static void printAiApi(cJSON* AiJson){
    puts("\n");

    if(AiJson != NULL){
        cJSON *textBlocks = cJSON_GetObjectItemCaseSensitive(AiJson, "text_blocks");
        cJSON *elements = NULL;
        if(!textBlocks){
            puts("La ricerca non ha prodotto risultati...");
            return;
        }

        puts("WELCOME IN FSEARCH...");
        puts("----------------------------------------------------------------------------------------");

        cJSON_ArrayForEach(elements, textBlocks){
            //extract title,text and lists from the 'text_blocks' json array
            cJSON *title = cJSON_GetObjectItemCaseSensitive(elements, "title");
            if(cJSON_IsString(title) && title->valuestring != NULL)
                printf("\n%s", title->valuestring);

            cJSON *paragraph = cJSON_GetObjectItemCaseSensitive(elements, "snippet");
            if(cJSON_IsString(paragraph) && paragraph->valuestring != NULL)
                printf("\n%s", paragraph->valuestring);

            
            cJSON *list = cJSON_GetObjectItemCaseSensitive(elements, "list");
            if(cJSON_IsArray(list)){
                //then I have to iterate through the list elements with another cJSON_ArrayForEach
                cJSON *elements1 = NULL;
                cJSON_ArrayForEach(elements1, list){
                    cJSON *listElement = cJSON_GetObjectItemCaseSensitive(elements1, "snippet");
                    if(cJSON_IsString(listElement) && listElement->valuestring != NULL)
                        printf("\n\n%s", listElement->valuestring);
                }
            }
            
        }

    }
    printf("\n\n\n\n");
}