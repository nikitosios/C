#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <curl/curl.h>
#include <curl/easy.h>

#define URL "http://lingust.ru/"

struct BufferData {
	char * buffer;
	size_t size;
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
		char *** nrussianp, size_t * s, struct BufferData * mem)
{
	size_t i = *ip;
	size_t q = *qp;
	size_t l;
	void * buffer = NULL;
	char ** russian = *russianp;
	char ** nrussian = *nrussianp;

	for (; strncmp(mem->buffer + i, "<strong>", strlen("<strong>"));
			i++);
	i += strlen("<strong>");
	for (q = i; strncmp(mem->buffer + q, "</strong>",
				strlen("</strong>")); q++);
	buffer = malloc(sizeof(char *) * n); memcpy(buffer, nrussian,
			sizeof(char *) * n);
	nrussian = (char **) realloc(nrussian, sizeof(char *) * (n + 1));
	memcpy(nrussian, buffer, sizeof(char *) * n);
	nrussian[n] = malloc((q - i) * sizeof(char *));
	memcpy(nrussian[n], mem->buffer + i, (q - i) * sizeof(char *));
	nrussian[n][q - i] = '\0';
	for (; strncmp(mem->buffer + i, "<br", strlen("<br")) &&
			strncmp(mem->buffer + i, "</div>", strlen("</div>")) &&
			strncmp(mem->buffer + i, "<span ", strlen("<span ")); i++);
	l = i;
	q = i;
	for (; mem->buffer[i] != '\n'; i--);
	for (; strncmp(mem->buffer + i - strlen("</strong>"), "</strong>",
				strlen("</strong>")); i++);
	for (; mem->buffer[i] == ' '; i++);
	memcpy(buffer, russian, sizeof(char *) * n);
	russian = (char **) realloc(russian, sizeof(char *) * (n + 1));
	memcpy(russian, buffer, sizeof(char *) * n);
	free(buffer);
	russian[n] = malloc(q - i);
	memcpy(russian[n], mem->buffer + i, q - i);
	russian[n][q - i] = '\0';
	if (!strncmp(mem->buffer + l, "</div>", strlen("</div>")))
	{
		size_t k = l + strlen("</div>");
		for (; mem->buffer[k] == ' ' || mem->buffer[k] == '\n'; k++);
		if (!strncmp(mem->buffer + k, "</div>", strlen("</div>"))) return 1;
	}

	*ip = i;
	*qp = q;
	(*s)++;
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
		lesson = "lezione1";
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
		for (int n = 0; n < 40; n++)
			if (parse(&i, &q, n, &russian, &nrussian, &s, mem)) break;
	}
	printf("All right.\n");

	free(mem->buffer);
	mem->size = 0;
	free(mem);

	for (int m = 0; (long) m < (long) s; m++)
		printf("%s - %s\n", nrussian[m], russian[m]);

	srand(time(NULL));
	char ** rus, ** nrus;
	rus = NULL;
	nrus = NULL;
	int q;
	for (int i = 0; (long) i < (long) s; i++)
	{
		q = rand() % (s - i);
		printf("i: %d, s: %ld, q: %d.\n", i, s, q);
		printf("Как будет %s на итальянском?\n", russian[q]);
		while (fgetc(stdin) != '\n');
		printf("%s\n", nrussian[q]);
		rus = malloc((s - i) * sizeof(char *));
		nrus = malloc((s - i) * sizeof(char *));
		memcpy(rus, russian, (s - i) * sizeof(char *));
		memcpy(nrus, nrussian, (s - i) * sizeof(char *));
		free(russian);
		free(nrussian);
		russian = malloc((s - i) * sizeof(char *));
		nrussian = malloc((s - i) * sizeof(char *));
		int j = 0;
		for (int p = 0; (long) p < (long) s; p++)
		{
			if (p != q)
			{
				russian[j] = rus[p];
				nrussian[j] = nrus[p];
				j++;
			}
		}
		free(rus);
		free(nrus);
	}
	return 0;
}
