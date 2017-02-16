#include "api.h"

char locked = 0;

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		if (!strcmp(argv[i], "--server"))
			return main_server(argc, argv);
	}

	return main_client(argc, argv);
}
