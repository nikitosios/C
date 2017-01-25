typedef struct xy {
	int x, y;
} xy;

WINDOW *create_newwin (int h, int w, int y, int x, unsigned int cp);
void destroy_win (WINDOW *win, unsigned int cp);
struct xy msgmove (void);
