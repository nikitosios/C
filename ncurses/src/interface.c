#include <string.h>
#include "header.h"
#include "interface.h"

int update_screen (void)
{
	const unsigned char bw = (COLS/8)%2 ? COLS/8-1 : COLS/8;

	/* initialize color pairs */
	init_pair(1, COLOR_BLACK,   COLOR_MAGENTA);
	init_pair(2, COLOR_BLACK,   COLOR_WHITE);
	init_pair(3, COLOR_WHITE,   COLOR_BLUE);
	init_pair(4, COLOR_BLACK,   COLOR_RED);
	init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(6, COLOR_WHITE,   COLOR_BLUE);
	/* set background of main ncurses window */
	bkgd(COLOR_PAIR(1));
	clear();
	/* create and draw all UI objects */
	msgbox = create_object(LINES/4,
			((COLS-BORD_WIDTH)/8*7+1)%2 ? (COLS-BORD_WIDTH)/8*7 : (COLS-BORD_WIDTH)/8*7+1,
			LINES - LINES/4, BORD_WIDTH, COLOR_PAIR(2), true);
	msgsend = create_object(msgbox.h, COLS - msgbox.w - BORD_WIDTH, msgbox.y, msgbox.ex+1,
			COLOR_PAIR(3), false);
	attron(COLOR_PAIR(3));
	mvaddstr(msgsend.cy, msgsend.cx-1, ">>>");
	attroff(COLOR_PAIR(3));
	filesend = create_object(msgbox.h, BORD_WIDTH, msgbox.y, 0, COLOR_PAIR(3), false);
	mvaddch(filesend.cy, filesend.cx, '#' | COLOR_PAIR(3));
	my_msgs = create_object(LINES-msgbox.h, COLS/2+1, 0, COLS/2, COLOR_PAIR(1), false);
	his_msgs = create_object(LINES-msgbox.h, COLS/2+1, 0, 0, COLOR_PAIR(1), false);
	my_msgs.win = newwin(my_msgs.h - 2, my_msgs.w - 1 - alarm_b.w, my_msgs.y + 1, my_msgs.x + 1);
	his_msgs.win = newwin(his_msgs.h - 2, his_msgs.w - 2 - alarm_b.w, his_msgs.y + 1, his_msgs.x + 1);
	wbkgd(my_msgs.win, COLOR_PAIR(1));
	wbkgd(his_msgs.win, COLOR_PAIR(1));
	for (int yi = his_msgs.y + 1; yi < his_msgs.ey; yi++)
		for (int xi = his_msgs.x + 1; xi < his_msgs.ex; xi++)
			mvaddch(yi, xi, ' ' | COLOR_PAIR(5));
	refresh();
	alarm_b = create_object((bw/2)%2 ? bw/2 : bw/2-1, bw, 0, COLS-bw,
			alarming ? COLOR_PAIR(2) : COLOR_PAIR(4), false);
	attron(alarming ? COLOR_PAIR(2) : COLOR_PAIR(4));
	mvaddstr(alarm_b.cy, alarm_b.cx-3, "[Ув.]");
	attroff(alarming ? COLOR_PAIR(2) : COLOR_PAIR(4));
	show_messages();
	update_msgbox();
	return 0;
}

/* constructor for UI objects */
struct object create_object (int h, int w, int y, int x, unsigned int flags, bool form)
{
	struct object obj;

	obj.h = h;
	obj.w = w;
	obj.y = y;
	obj.x = x;
	obj.ey = obj.y + obj.h - 1;
	obj.ex = obj.x + obj.w - 1;
	obj.cy = obj.h/2 + obj.y;
	obj.cx = obj.w/2 + obj.x;
	obj.win = create_newwin(obj.h, obj.w, obj.y, obj.x, flags);
	for (int yi = obj.y+1; yi < obj.ey; yi++)
		for (int xi = obj.x+1; xi < obj.ex; xi++)
			mvaddch(yi, xi, ' ' | flags);
	return obj;
}

/* constructor for windows */
WINDOW *create_newwin (int h, int w, int y, int x, unsigned int cp)
{
	WINDOW *win;

	win = newwin(h, w, y, x);
	wborder(win, '|' | cp, '|' | cp, '-' | cp, '-' | cp, '+' | cp, '+' | cp, '+' | cp, '+' | cp);
	refresh();
	wrefresh(win);
	return win;
}

/* how many lines in given message */
int how_many_lines (unsigned char *message)
{
	int lines = 0;
	int sym = 0;

	for (int i = 0; i < strlen(message); ++i) {
		if (message[i] == '\n' || sym >= my_msgs.w) {
			++lines;
			sym = 0;
		}
		++sym;
	}
	return lines;
}

/* compare strings */
int onestr (char *str1, char *str2)
{
	if (strlen(str1) != strlen(str2))
		return 0;
	for (int i = 0; i < strlen(str2); ++i)
		if (str1[i] != str2[i])
			return 0;
	return 1;
}

/* draw all messages */
int draw_msgs (unsigned char *msg)
{
	int tab = -1, it = 0, it_r;
	unsigned char nick[41];
	int curY2;

	/* find first tabulation symbol in array */
	for (tab = it; tab < strlen(msg); ++tab) {
		if (msg[tab] == '\t')
			break;
	}

	if (tab != -1) {
		/* read nickname */
		for (it = tab; it != 0 && msg[it - 1] != '\n'; --it);
		for (it = it; msg[it] != '\t'; ++it)
			nick[it] = msg[it];
		nick[it - 1] = '\0';

		/* if it is your message then draw it to right msessages window */
		it = tab + 2;
		if (onestr(nick, my_nickname)) {
			/* get last line of previous message to draw current message lower */
			it_r = it;
			for (it = tab; it != 0 && msg[it - 1] != '\n'; --it);
			getyx(his_msgs.win, curY, curX);
			getyx(my_msgs.win, curY2, curX);
			wmove(my_msgs.win, curY > curY2 ? curY : curY2, 0);
			/* draw nickname */
			for (int i = it; msg[i] != '\t'; ++i)
				waddch(my_msgs.win, msg[i] | COLOR_PAIR(6) | A_BOLD);
			waddch(my_msgs.win, '\n' | COLOR_PAIR(5));
			/* draw current message and handle all next messages using this function (recursively) */
			for (it = it_r; it < strlen(msg); ++it) {
				if (msg[it] != '\t')
					waddch(my_msgs.win, msg[it] | COLOR_PAIR(3));
				else {
					it_r = it + 1;
					while (msg[it - 1] != '\n') {
						--it;
						getyx(my_msgs.win, curY, curX);
						mvwaddch(my_msgs.win, curY, curX - 1, ' ' | COLOR_PAIR(5));
						wmove(my_msgs.win, curY, curX - 1);
					}
					draw_msgs(msg + it);
					break;
				}
			}
			/* refresh window */
			wrefresh(my_msgs.win);
		/* else to left */
		} else {
			it_r = it;
			for (it = tab; it != 0 && msg[it - 1] != '\n'; --it);
			getyx(my_msgs.win, curY, curX);
			getyx(his_msgs.win, curY2, curX);
			wmove(his_msgs.win, curY > curY2 ? curY : curY2, 0);
			for (int i = it; msg[i] != '\t'; ++i)
				waddch(his_msgs.win, msg[i] | COLOR_PAIR(2) | A_BOLD);
			waddch(his_msgs.win, '\n' | COLOR_PAIR(5));
			for (it = it_r; it < strlen(msg); ++it) {
				if (msg[it] != '\t')
					waddch(his_msgs.win, msg[it] | COLOR_PAIR(2));
				else {
					it_r = it + 1;
					while (msg[it - 1] != '\n') {
						--it;
						getyx(his_msgs.win, curY, curX);
						mvwaddch(his_msgs.win, curY, curX - 1, ' ' | COLOR_PAIR(5));
						wmove(his_msgs.win, curY, curX - 1);
					}
					draw_msgs(msg + it);
					break;
				}
			}
			wrefresh(his_msgs.win);
		}


		return tab + 2;
	} else return -1;
}

int show_messages (void)
{
	int history_size = 0, it, f = 0;
	unsigned char bw = (COLS/8)%2 ? COLS/8-1 : COLS/8;
	unsigned char msg[10000] = { '\0' };

	/* read last 10000 symbols from history file to memory */
	system("touch history.txt");
	history = fopen("history.txt", "r");
	fseek(history, 0, SEEK_END);
	history_size = ftell(history);
	if (!history_size) {
		fclose(history);
		return 0;
	}
	if (history_size > 10000)
		fseek(history, history_size - 10000, SEEK_SET);
	else
		fseek(history, 0, SEEK_SET);
	it = 0;
	for (int i = ftell(history); i < history_size; ++i) {
		msg[it] = fgetc(history);
		++it;
	}
	fclose(history);
	msg[it] = '\0';

	/* handle offset */
	unsigned char *msgP = msg;
	int lines = how_many_lines(msg);
	if (lines > my_msgs.h) {
		for (int i = 0; i < strlen(msg); ++i) {
		}
	}
	f = 0;
	for (int i = 0; i < msgsoffs; ++i)
		if (msg[i] == '\n') {
			++i;
			msgP = msg + i;
		}

	for (it = msgP - msg; msg[it] != '\t'; ++it)
		if (msg[it] == '\n')
			f = 1;
	if (f) {
		for (it = msgP - msg; msg[it] != '\t'; --it);
		for (--it; it > 0 && msg[it - 1] != '\n'; --it);
		unsigned char nick[41];
		int iter = 0;
		for (+it; msg[it + 1] != '\t'; ++it) {
			nick[iter] = msg[it];
			++iter;
		}
		if (onestr(nick, my_nickname)) {
			for (msgP; *msgP != '\t'; ++msgP)
				waddch(my_msgs.win, *msgP | COLOR_PAIR(6));
			waddch(my_msgs.win, '\n' | COLOR_PAIR(5));
		} else {
			for (msgP; *msgP != '\t'; ++msgP)
				waddch(his_msgs.win, *msgP | COLOR_PAIR(3));
			waddch(his_msgs.win, '\n' | COLOR_PAIR(5));
		}
		msgP += 2;
	}

	/* draw messages from memory */
	draw_msgs(msgP);

	/* draw alarm button again */
	alarm_b = create_object((bw/2)%2 ? bw/2 : bw/2-1, bw, 0, COLS-bw,
			alarming ? COLOR_PAIR(2) : COLOR_PAIR(4), false);
	attron(alarming ? COLOR_PAIR(2) : COLOR_PAIR(4));
	mvaddstr(alarm_b.cy, alarm_b.cx-3, "[Ув.]");
	attroff(alarming ? COLOR_PAIR(2) : COLOR_PAIR(4));
	refresh();
	return 0;
}

struct xy msgmove (void)
{
	struct xy st;
	st.y = msgbox.y+1, st.x = msgbox.x+1;
	char f = 0;
	unsigned char *it;
	int offs = 0;

	for (it = my_msg; offs < msgoffset; ++it)
		if (*it == '\n')
			++offs;
	for (unsigned char *i = it; i < my_msgP; ++i) {
		if (*i >= 128) {
			if (!f) {
				++st.x;
				f = 1;
			} else f = 0;
		} else ++st.x;
		if (*i == '\n') {
			++st.y;
			st.x = msgbox.x+1;
		} else if (st.x >= msgbox.ex) {
			++st.y;
			st.x = msgbox.x+1;
		}
	}
	return st;
}

/* draw all required elements to textbox for messages */
int update_msgbox (void)
{
	unsigned char *it;
	int offs = 0;

	for (int y = msgbox.y+1; y < msgbox.ey; ++y)
		for (int x = msgbox.x+1; x < msgbox.ex; ++x)
			mvaddch(y, x, ' ' | COLOR_PAIR(2));
	move(msgbox.y+1, msgbox.x+1);
	for (it = my_msg; offs < msgoffset; ++it)
		if (*it == '\n')
			++offs;
	for (unsigned char *i = it; i < my_msgEP; ++i) {
		if (*i != '\n') {
			getyx(stdscr, curY, curX);
			if (curX >= msgbox.ex)
				move(curY+1, msgbox.x+1);
			if (curY < msgbox.ey)
				addch(*i | COLOR_PAIR(2));
		} else {
			getyx(stdscr, curY, curX);
			move(curY+1, msgbox.x+1);
		}
	}
	struct xy msgmove_ret = msgmove();
	move(msgmove_ret.y, msgmove_ret.x);
	refresh();
	return 0;
}
