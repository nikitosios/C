#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <curl/curl.h>

#define BUFLEN 1000000

void * buffer;
size_t buflen, n;

int main (void)
{
    buffer = malloc(BUFLEN);
    buflen = BUFLEN;

    printf("Parser started.\n");
    CURL * curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, "https://github.com");
        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1);
        res = curl_easy_perform(curl);
        curl_easy_recv(curl, buffer, buflen, &n);
        curl_easy_cleanup(curl);
    }

    printf("%s\n", (char *)buffer);
    free(buffer);
    return 0;
}
