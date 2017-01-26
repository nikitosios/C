#include <ncurses.h> /* include ncurses (for console colorful UI) */
#include "header.h" /* include my header with global variables and functions */

/* declare UI objects */
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
unsigned char my_nickname[41] = "nikitosios";
int msgsoffs;

int parse_mouse (MEVENT event, struct object button);

int main (void)
{	
	short c;
	MEVENT event;

	/* initialize variables and ncurses */
	msgoffset = 0;
	msgsoffs = 0;
	my_msgEP = my_msgP = my_msg;
	alarming = true;
	setlocale(LC_ALL, ""); /* gives ability to get and show russian symbols */
	initscr(); /* initialize main ncurses window */
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS, NULL); /* for mouse events */
	start_color(); /* for ability to show different colors */
	refresh(); /* refresh main ncurses window */
	
	update_screen(); /* show all UI objects with content on screen */
	move(msgbox.y+1, msgbox.x+1);
	/* main loop */
	while (1) {
		switch (c = getch()) {
			/* parse mouse events */
			case KEY_MOUSE:
				if (getmouse(&event) == OK) {
					if (event.bstate & BUTTON1_CLICKED) {
						if (parse_mouse(event, alarm_b)) {
							alarming = alarming ? false : true; /* toggle alarm flag */
							update_screen();
						}
						/* if pressed "send message" button */
						if (parse_mouse(event, msgsend)) {
							if (my_msgEP != my_msg) {
								/* delete extra \n symbols */
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
								/* add message to history file and send */
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
				}
				break;
			/* handling pressed arrow keys */
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
			/* if it is normal symbol, process it by parse_ch() function (in file parse_ch.c) */
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

/* this function will send message to reciever */
int send_message (unsigned char *msg)
{
	return 0;
}

/* format message with special symbols and additional information */
char *msgformat (unsigned char *msg)
{
	return 0;
}

/* verify that was pressed given button */
int parse_mouse (MEVENT event, struct object button)
{
	if (event.x <= button.ex && event.x >= button.x && event.y <= button.ey && event.y >= button.y)
		return 1;
	return 0;
}

/* how many lines are between my_msg and given pointer */
int msggetstrn (unsigned char *pointer)
{
	int str = 1;

	for (unsigned char *i = my_msg; i < pointer; ++i)
		if (*i == '\n')
			++str;
	return str;
}

/* how many symbols are in given line */
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

/* positioning pointer to given coords */
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
