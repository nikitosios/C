#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <curl/curl.h>
#include <curl/easy.h>

struct BufferStruct
{
    char * buffer;
    size_t size;
};

static size_t write_callback (void * ptr, size_t size, size_t nmemb,
        void * data)
{
    size_t realsize = size * nmemb;
    struct BufferStruct * mem = (struct BufferStruct *) data;

    mem->buffer = realloc(mem->buffer, mem->size + realsize + 1);

    if (mem->buffer)
    {
        memcpy(&(mem->buffer[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->buffer[mem->size] = 0;
    }

    return realsize;
}

int main (void)
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL * curl;
    CURLcode result;
    struct BufferStruct output;

    output.buffer = NULL;
    output.size = 0;
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&output);
    curl_easy_setopt(curl, CURLOPT_URL, "https://freelancehunt.com");
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    FILE * fp;
    fp = fopen("page.html", "w");
    if (!fp) return 1;
    fprintf(fp, output.buffer);
    fclose(fp);

    if (output.buffer)
    {
        free(output.buffer);
        output.buffer = 0;
        output.size = 0;
    }

    printf("\nLibcurl rules!\n");
    return 0;
}
