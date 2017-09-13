#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <curl/curl.h>

#define BUFLEN 1000000

int main (void)
{
    void * buffer;
    size_t buflen, n;
    curl_socket_t sockfd;
    CURLcode res;
    CURL * curl;

    buflen = BUFLEN;
    buffer = malloc(buflen);

    printf("Parser started.\n");
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://github.com");
        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            printf("Error: %s\n", curl_easy_strerror(res));
            return 1;
        }

        res = curl_easy_getinfo(curl, CURLINFO_ACTIVESOCKET, &sockfd);
        if (res != CURLE_OK) {
            printf("Error: %s\n", curl_easy_strerror(res));
            return 1;
        }

        curl_easy_recv(curl, buffer, buflen, &n);
        curl_easy_cleanup(curl);
    }

    printf("%i bytes recieved.\n%s\n", n, (char *)buffer);
    free(buffer);
    return 0;
}
