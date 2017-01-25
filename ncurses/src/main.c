#include <ncurses.h>
#include "header.h"

#define GO_UP 1
#define GO_DOWN 2
#define GO_LEFT 3
#define GO_RIGHT 4

//#define _DEBUG
#if defined(_DEBUG)
FILE *d;
#endif

struct object msgsend;
struct object msgbox;
struct object filesend;
struct object alarm_b;
struct object my_msgs;
struct object his_msgs;

bool alarming;
unsigned char my_msg[MSG_SIZE];
unsigned char *my_msgP;
unsigned char *my_msgEP;
int msgoffset;
int curY, curX;
FILE *history;

int parse_mouse (MEVENT event, struct object button);

int main (void)
{	
	short c;
	MEVENT event;
	unsigned char my_nickname[41] = "Nikitosios";

	/* Initialize curses */
	msgoffset = 0;
	my_msgEP = my_msgP = my_msg;
	msgoffset = 0;
	alarming = true;
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS, NULL);
	start_color();
	refresh();
	
	update_screen();
	move(msgbox.y+1, msgbox.x+1);
	while (1) {
		switch (c = getch()) {
			case KEY_MOUSE:
				if (getmouse(&event) == OK) {
					if (event.bstate & BUTTON1_CLICKED) {
						if (parse_mouse(event, alarm_b)) {
							alarming = alarming ? false : true;
							update_screen();
						}
						if (parse_mouse(event, msgsend)) {
							if (my_msgEP != my_msg) {
								if (*(my_msgEP - 1) != '\n') {
									*my_msgEP = '\n';
									++my_msgEP;
								}
								while (1) {
									if (*(my_msgEP - 2) != '\n')
										break;
									else
										--my_msgEP;
								}
								history = fopen("history.txt", "a");
								fprintf(history, "%s:\t\n", my_nickname);
								for (unsigned char *i = my_msg; i < my_msgEP; ++i)
									fputc(*i, history);
								fclose(history);
								show_messages();
								my_msgEP = my_msg;
								my_msgP = my_msg;
								msgoffset = 0;
								update_screen();
							}
						}
					}
					if (event.bstate & BUTTON3_CLICKED) {
						++msgoffset;
						update_msgbox();
					}
				}
				break;
			case KEY_UP:
				if (msggetstrn(my_msgP) != 1) {
					getyx(stdscr, curY, curX);
					if (curY <= msgbox.y + 1)
						--msgoffset;
					msggo(msggetstrn(my_msgP) - 1, msggetsymn());
				}
				break;
			case KEY_DOWN:
				if (msggetstrn(my_msgP) != msggetstrn(my_msgEP)) {
					getyx(stdscr, curY, curX);
					if (curY >= msgbox.ey - 1)
						++msgoffset;
					msggo(msggetstrn(my_msgP) + 1, msggetsymn());
				}
				break;
			case KEY_LEFT:
				if (my_msgP > my_msg && *(my_msgP - 1) != '\n') {
					--my_msgP;
					if (*my_msgP >= 128)
						--my_msgP;
					update_msgbox();
				}
				break;
			case KEY_RIGHT:
				if (my_msgP < my_msgEP && *my_msgP != '\n') {
					++my_msgP;
					if (*my_msgP >= 128)
						++my_msgP;
					update_msgbox();
				}
				break;
			default:
				if (c != ERR)
					parse_ch(c);
				break;
		}
	}

	getch();
	endwin();
	return 0;
}

int send_message (unsigned char *msg)
{
	return 0;
}

char *msgformat (unsigned char *msg)
{
	return 0;
}

int parse_mouse (MEVENT event, struct object button)
{
	if (event.x <= button.ex && event.x >= button.x && event.y <= button.ey && event.y >= button.y)
		return 1;
	return 0;
}

int msggetstrn (unsigned char *pointer)
{
	int str = 1;

	for (unsigned char *i = my_msg; i < pointer; ++i)
		if (*i == '\n')
			++str;
	return str;
}

int msggetsymn (void)
{
	int sym = 0;
	unsigned char *it, f = 0;

	for (it = my_msgP; *(it - 1) != '\n' && (it - 1) != my_msg - 1; --it);
	for (unsigned char *i = it; i < my_msgP; ++i) {
		if (*i >= 128) {
			if (!f) {
				++sym;
				f = 1;
			} else f = 0;
		} else ++sym;
	}
	return sym;
}

int msggo (int y, int x)
{
	int n = 1, f = 0;
	unsigned char *yp, *p = NULL;

	for (yp = my_msg; n < y; ++yp)
		if (*yp == '\n')
			++n;
	n = 0;
	for (unsigned char *i = yp; *i != '\n' && i < my_msgEP; ++i)
		if (*i < 128) {
			++n;
		} else if (!f) {
			++n;
			f = 1;
		} else f = 0;
	if (x > n)
		x = n;
	n = 0;
	f = 0;
	for (unsigned char *i = yp; n <= x; ++i) {
		if (*i < 128)
			++n;
		else if (!f) {
			++n;
			f = 1;
		} else f = 0;
		p = i;
	}
	my_msgP = p;
	update_msgbox();
	return 0;
}
