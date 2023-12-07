#ifndef CURL_INTERFACE_H
#define CURL_INTERFACE_H

#include <curl/curl.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    CURL * curl;
    CURLcode * res;
    struct curl_slist * headers;
} CurlHandle_t; 

CurlHandle_t *curl_init(char *url, uint8_t u8_numHeaders, ...);
CURLcode curl_post(CurlHandle_t *curlHandle, char *postData, size_t (*callBackFunc)(void *, size_t, size_t, void *));

#endif /* CURL_INTERFACE_H */
