#ifndef SETUP_CURL_CJSON_H
#define SETUP_CURL_CJSON_H

#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

void setupCurl(char *prompt, char *apiURL, char *jsonReportFile);
cJSON *setupJson(char *jsonReportFile);

#endif