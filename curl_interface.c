#include "curl_interface.h"

CurlHandle_t *curl_init(char *url, uint8_t u8_numHeaders, ...)
{
    va_list(args);
    va_start(args, u8_numHeaders);

    CurlHandle_t* newCurl = (CurlHandle_t *) malloc(sizeof(CurlHandle_t));

    newCurl->curl = NULL;
    newCurl->headers = NULL;
    newCurl->res = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    newCurl->curl = curl_easy_init();

    curl_easy_setopt(newCurl->curl, CURLOPT_URL, url);
    curl_easy_setopt(newCurl->curl, CURLOPT_SSL_VERIFYPEER, 0L); // Work on fixing this line because bad practice.

    for (uint8_t u8_i = 0; u8_i < u8_numHeaders; u8_i++)
    {
        newCurl->headers = curl_slist_append(newCurl->headers, va_arg(args, char*));
    }

    curl_easy_setopt(newCurl->curl, CURLOPT_HTTPHEADER, newCurl->headers);

    return newCurl;
}

CURLcode curl_post(CurlHandle_t *curlHandle, char *postData, size_t (*callBackFunc)(void *, size_t, size_t, void *))
{
    CURLcode retVal = CURLE_SEND_ERROR;

    curl_easy_setopt(curlHandle->curl, CURLOPT_WRITEFUNCTION, callBackFunc);
    curl_easy_setopt(curlHandle->curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curlHandle->curl, CURLOPT_POSTFIELDS, postData);

    retVal = curl_easy_perform(curlHandle->curl);

    return retVal;
}
