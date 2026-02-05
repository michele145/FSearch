#include "setupCurlCjson.h"

void setupCurl(char *prompt, char *apiURL, char *jsonReportFile){
    CURL *curl = curl_easy_init();
    if(curl == NULL){
        puts("Errore nella libreria curl!");
        exit(1);
    }

    FILE *outputFile = fopen(jsonReportFile, "w");
    if(outputFile == NULL){
        puts("Errore nell apertura del file JSON!");
        exit(1);
    }

    curl_easy_setopt(curl, CURLOPT_URL, apiURL); //make the request at this URL
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, outputFile); //and stores the response in the output JSON file
    int result = curl_easy_perform(curl); //makes the request
    fclose(outputFile);
    curl_easy_cleanup(curl);
    if(result != CURLE_OK){
        puts("Errore nella richiesta curl!");
        exit(1);
    }
}



cJSON *setupJson(char *jsonReportFile){
    //I open the file where the JSON report is saved
    FILE *inputFile = fopen(jsonReportFile, "r");

    /* Seek to the end of the file so we can determine the total number
      of characters then create an array large enough to store the
      entire file as a string. The subsequent ftell call returns the 
      file-position pointer's location. */

    fseek(inputFile, 0L, SEEK_END);
    long count = ftell(inputFile);

    char json[count + 1];
    
    fseek(inputFile, 0L, SEEK_SET);
    fread(json, sizeof(char), count, inputFile);
    json[count] = '\0';
    fclose(inputFile);


    cJSON *parsedJson = cJSON_Parse(json);
    
    return parsedJson;
}