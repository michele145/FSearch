#include "setupCurlCjson.h"

void setupCurl(char *prompt, char *apiURL, char *jsonReportFile){
    CURL *curl = curl_easy_init();
    if(curl == NULL){
        perror("Error in curl library!");
        exit(1);
    }

    FILE *outputFile = fopen(jsonReportFile, "w");
    if(outputFile == NULL){
        perror("Error opening JSON file!");
        exit(1);
    }

    curl_easy_setopt(curl, CURLOPT_URL, apiURL); //make the request at this URL
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, outputFile); //and stores the response in the output JSON file
    int result = curl_easy_perform(curl); //makes the request
    fclose(outputFile);
    curl_easy_cleanup(curl); //handle closing
    if(result != CURLE_OK){
        perror("Error in curl request!");
        exit(1);
    }
}



cJSON *setupJson(char *jsonReportFile){
    //I open the file where the JSON report is saved
    FILE *inputFile = fopen(jsonReportFile, "r");

    if(inputFile == NULL){
        perror("Error opening JSON file(1)!");
        exit(1);
    }

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