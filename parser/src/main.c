#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <curl/curl.h>
#include <curl/easy.h>

#define TABLE "<table class=\"table table-normal\" "
#define TBODY "<tbody>"
#define TR "<tr "
#define TD "<td "
#define A "<a "
#define LT "<"
#define GT ">"

#define FILENAME "data"

struct BufferData {
    char * buffer;
    size_t size;
};

static size_t write_null (void * ptr, size_t size, size_t nmemb, void * data)
{
    return size * nmemb;
}

static size_t write_callback (void * ptr, size_t size, size_t nmemb, void * data)
{
    struct BufferData * mem = (struct BufferData *) data;
    size_t realsize = size * nmemb;

    mem->buffer = realloc(mem->buffer, mem->size + realsize + 1);
    if (mem->buffer)
    {
        memcpy(mem->buffer + mem->size, ptr, realsize);
        mem->size += realsize;
        mem->buffer[mem->size] = 0;
    }

    return realsize;
}

void parse (void)
{
    CURL * curl;
    CURLcode res;
    struct BufferData mem;

    mem.buffer = NULL;
    mem.size = 0;

    printf("CURL is working...\n");
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_null);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0");
        curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
        curl_easy_setopt(curl, CURLOPT_URL,
                "https://freelancehunt.com/profile/login");

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            printf("Error: %s\n", curl_easy_strerror(res));
            exit(1);
        }

        curl_easy_setopt(curl, CURLOPT_REFERER,
                "https://freelancehunt.com/profile/login");
        char * data = "_qf__login_form=&login=nikitosios&password=NikitosIOS20IOS031xD%3F&remember_me=1&save=";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            printf("Error: %s\n", curl_easy_strerror(res));
            exit(1);
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &mem);
        curl_easy_setopt(curl, CURLOPT_URL, "https://freelancehunt.com/projects?only_my_skills=1&only_safe=1");
        curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    } else exit(1);

    printf("Page loaded.\n");

    char * title;
    char ** titles = NULL;
    int titlesn = 0;
    size_t w, q;

    FILE * f = fopen("page.html", "w");
    fprintf(f, "%s", mem.buffer);
    fclose(f);
    for (w = 0; strncmp(mem.buffer + w, TABLE, strlen(TABLE)); w++);
    for (; strncmp(mem.buffer + w, TBODY, strlen(TBODY)); w++);
    for (; strncmp(mem.buffer + w, TR, strlen(TR)); w++);

    titles = malloc(sizeof(char *) * 15);
    for (int j = 0; j < 15; j++) {
        title = malloc(512);
        for (; strncmp(mem.buffer + w, TD, strlen(TD)); w++);
        for (; strncmp(mem.buffer + w, A, strlen(A)); w++);
        for (; strncmp(mem.buffer + w, GT, strlen(GT)); w++);
        w++;
        q = w;
        for (; strncmp(mem.buffer + w, LT, strlen(LT)); w++);
        strncpy(title, mem.buffer + q, w - q);
        title[w - q + 1] = 0;
        titles[j] = title;
        titlesn++;
        printf("%s\n", title);
        for (q = w; strncmp(mem.buffer + q, "</tr>",
                    strlen("</tr>")); q++);
        q += strlen("</tr>");
        for (; strncmp(mem.buffer + q, LT, strlen(LT)); q++);
        if (!strncmp(mem.buffer + q, "</tbody>", strlen("</tbody>")))
            break;
        for (; strncmp(mem.buffer + w, TR, strlen(TR)); w++);
    }

    char c;
    FILE * file = fopen(FILENAME, "r+");
    if (!file) file = fopen(FILENAME, "w+");
    if (!file) exit(1);
    if (fgetc(file) != EOF) {
        fseek(file, 0, SEEK_SET);
        char * string = malloc(256000);
        int i = 0;
        while ((c = fgetc(file)) != EOF)
        {
            string[i] = c;
            i++;
        }
        string[i] = '\0';
        printf("String %s found.\n", string);
        i = 0;
        while (i < titlesn && strcmp(titles[i], string))
        {
            system("mpv alarm.mp3 &");
            printf("%s\n", titles[i]);
            i++;
        }
    }
    fprintf(file, "%s", titles[0]);
    fclose(file);

    free(mem.buffer);
    mem.buffer = NULL;
    mem.size = 0;

    return;
}

int main (void) {
    while (1)
    {
        parse();
        system("sleep 900");
    }
    return 0;
}
