#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <curl/curl.h>
#include <curl/easy.h>
#define URL "http://lingust.ru/"

struct BufferData { char * buffer; size_t size;
};

static size_t write_callback (void * ptr, size_t size, size_t nmemb,
		void * data)
{
	size_t realsize = size * nmemb;
	struct BufferData * mem = data;

	mem->buffer = realloc(mem->buffer, mem->size + realsize + 1);
	if (mem->buffer)
	{
		memcpy(mem->buffer + mem->size, ptr, realsize);
		mem->size += realsize;
		mem->buffer[mem->size] = 0;
	}
	return realsize;
}

int parse (size_t * ip, size_t * qp, int n, char *** russianp,
		char *** nrussianp, struct BufferData * mem)
{
	size_t i = *ip;
	size_t q = *qp;
	size_t l;
	void * buffer = NULL;
	char ** russian = *russianp;
	char ** nrussian = *nrussianp;

	for (; strncmp(mem->buffer + i, "<strong>", strlen("<strong>")); i++);
	i += strlen("<strong>");
	for (q = i; strncmp(mem->buffer + q, "</strong>",
				strlen("</strong>")); q++);
	buffer = malloc(sizeof(char *) * n);
	memcpy(buffer, nrussian, sizeof(char *) * n);
	nrussian = (char **) realloc(nrussian, sizeof(char *) * (n + 1));
	memcpy(nrussian, buffer, sizeof(char *) * n);
	nrussian[n] = malloc((q - i) * sizeof(char *));
	memcpy(nrussian[n], mem->buffer + i, (q - i) * sizeof(char *));
	nrussian[n][q - i] = '\0';
	size_t j;
	for (j = 0; j < strlen(nrussian[n]) && (nrussian[n][j] == '\n' ||
				nrussian[n][j] == ' '); j++);
	nrussian[n] = nrussian[n] + j;
	for (j = strlen(nrussian[n]) - 1; nrussian[n][j] == '\n' ||
			nrussian[n][j] == ' '; j--);
	nrussian[n][j + 1] = '\0';
	i = q + strlen("</strong>");
	for (q = i; strncmp(mem->buffer + q, "<br", strlen("<br")) &&
			strncmp(mem->buffer + q, "</div>", strlen("</div>")) &&
			strncmp(mem->buffer + q, "<span ", strlen("<span ")); q++);
	l = q;
	memcpy(buffer, russian, sizeof(char *) * n);
	russian = (char **) realloc(russian, sizeof(char *) * (n + 1));
	memcpy(russian, buffer, sizeof(char *) * n);
	free(buffer);
	russian[n] = malloc(q - i + 1);
	memcpy(russian[n], mem->buffer + i, q - i);
	russian[n][q - i] = '\0';
	for (j = 0; j < strlen(russian[n]) && (russian[n][j] == '\n' ||
				russian[n][j] == ' '); j++);
	russian[n] = russian[n] + j;
	for (j = strlen(russian[n]) - 1; russian[n][j] == '\n' ||
			russian[n][j] == ' '; j--);
	russian[n][j + 1] = '\0';
	if (!strncmp(mem->buffer + l, "</div>", strlen("</div>")))
	{
		size_t k = l + strlen("</div>") + 1;
		for (; mem->buffer[k] == ' ' || mem->buffer[k] == '\n'; k++);
		if (!strncmp(mem->buffer + k, "</div>", strlen("</div>"))) return 1;
	}
	i = q;

	*ip = i;
	*qp = q;
	*russianp = russian;
	*nrussianp = nrussian;
	return 0;
}

int main (int argc, char ** argv)
{
	CURL * curl;
	char url[512];
	char * language;
	char * lesson;
	char ** russian;
	char ** nrussian;
	size_t s = 0;
	struct BufferData * mem = malloc(sizeof (struct BufferData));

	mem->buffer = NULL;
	mem->size = 0;
	russian = NULL;
	nrussian = NULL;

	if (argc > 1) {
		language = malloc(sizeof argv[1]);
		lesson = malloc(sizeof argv[2]);
		memcpy(language, argv[1], strlen(argv[1]) + 1);
		memcpy(lesson, argv[2], strlen(argv[2]) + 1);
	} else {
		language = "italiano/italiano-lezioni";
		lesson = "lezione6";
	}

	memcpy(url, URL, strlen(URL));
	memcpy(url + strlen(URL), language, strlen(language));
	url[strlen(URL) + strlen(language)] = '/';
	memcpy(url + strlen(URL) + strlen(language) + 1, lesson, strlen(lesson));
	url[strlen(URL) + 1 + strlen(language) + strlen(lesson)] = '\0';

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, mem);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux "
				"x86_6    4; rv:52.0) Gecko/20100101 Firefox/52.0");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	} else return 1;

	if (mem->buffer) {
		size_t i, q;
		for (i = 0; strncmp(mem->buffer + i, "Словарь", strlen("Словарь"));
				i++);
		for (int n = 0;; n++) {
			if (parse(&i, &q, n, &russian, &nrussian, mem)) {
				s = n + 1;
				break;
			}
			s = n + 1;
		}
	}

	free(mem->buffer);
	mem->size = 0;
	free(mem);

	srand(time(NULL));
	char * buf;
    int pos, pos2;
    for (size_t i = 0; i < rand() % 50 + s; i++)
    {
        pos = rand() % s;
        pos2 = rand() % s;
		
        buf = russian[pos];
        russian[pos] = russian[pos2];
        russian[pos2] = buf;

		buf = nrussian[pos];
		nrussian[pos] = nrussian[pos2];
		nrussian[pos2] = buf;
    }
	for (size_t i = 0; i < s; i++) {
		printf("Как будет %s по-итальянски?\n", russian[i]);
		while (fgetc(stdin) != '\n');
		printf("%s\n\n", nrussian[i]);
	}
	free(russian);
	free(nrussian);
	return 0;
}
