#include <string.h>
#include "header.h"
#include "interface.h"

int update_screen (void)
{
	unsigned char bw = (COLS/8)%2 ? COLS/8-1 : COLS/8;

	init_pair(1, COLOR_BLACK,   COLOR_MAGENTA);
	init_pair(2, COLOR_BLACK,   COLOR_WHITE);
	init_pair(3, COLOR_BLACK,   COLOR_BLUE);
	init_pair(4, COLOR_BLACK,   COLOR_RED);
	init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA); init_pair(6, COLOR_WHITE,   COLOR_BLUE); bkgd(COLOR_PAIR(1));
	clear();
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
	my_msgs.win = newwin(my_msgs.h - 2, my_msgs.w - 2, my_msgs.y + 1, my_msgs.x + 1);
	his_msgs.win = newwin(his_msgs.h - 2, his_msgs.w - 2, his_msgs.y + 1, his_msgs.x + 1);
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

WINDOW *create_newwin (int h, int w, int y, int x, unsigned int cp)
{
	WINDOW *win;

	win = newwin(h, w, y, x);
	wborder(win, '|' | cp, '|' | cp, '-' | cp, '-' | cp, '+' | cp, '+' | cp, '+' | cp, '+' | cp);
	refresh();
	wrefresh(win);
	return win;
}

void destroy_win (WINDOW *win, unsigned int cp)
{
	wborder(win, ' ' | cp, ' ' | cp, ' ' | cp, ' ' | cp, ' ' | cp, ' ' | cp, ' ' | cp, ' ' | cp);
	wrefresh(win);
	delwin(win);
	return;
}

int how_many_lines (unsigned char *message)
{
	int lines = 0;
	int i = 0;

	while (message[i] != '\0') {
		if (message[i] == '\n')
			++lines;
		++i;
	}
	return lines;
}

int show_messages (void)
{
	int history_size = 0, it;
	unsigned char bw = (COLS/8)%2 ? COLS/8-1 : COLS/8;
	unsigned char msg[21000] = { '\0' };

	system("touch history.txt");
	history = fopen("history.txt", "r");
	fgetc(history);
	fseek(history, 0, SEEK_END);
	history_size = ftell(history);
	if (history_size > 21000)
		fseek(history, history_size - 21000, SEEK_SET);
	else
		fseek(history, 0, SEEK_SET);
	it = 0;
	for (int i = ftell(history); i < history_size; ++i) {
		msg[it] = fgetc(history);
		++it;
	}
	fclose(history);
	msg[it] = EOF;

	FILE *d = fopen("debug.log", "a");
	fprintf(d, "%i", how_many_lines(msg));
	fclose(d);

	wrefresh(my_msgs.win);
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
