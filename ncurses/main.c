#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ncurses.h>
#include <panel.h>
#include <menu.h>
#include <form.h>

int main (void)
{
	WINDOW *my_wins[8];
	PANEL my_panels[8];
	int ch;

	initscr();
	start_color();
	noecho();
	raw();
	keypad(stdscr, TRUE);
	refresh();

	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_BLUE);
	init_pair(4, COLOR_BLACK, COLOR_WHITE);

	float maxx, maxy;
	getmaxyx(stdscr, maxy, maxx);

	my_wins[0] = newwin(roundf(maxy / 5), roundf(maxx / 8), 0, 0);
	my_wins[1] = newwin(roundf(maxy / 5), roundf(maxx / 8 * 6), 0, roundf(maxx / 8));
	my_wins[2] = newwin(roundf(maxy / 5), roundf(maxx / 8), 0, roundf(maxx - maxx / 8));
	my_wins[3] = newwin(roundf(maxy / 5 * 3), roundf(maxx / 2), roundf(maxy / 5 + 1), 0);
	my_wins[4] = newwin(roundf(maxy / 5 * 3), roundf(maxx / 2), roundf(maxy / 5 + 1), roundf(maxx / 2));
	my_wins[5] = newwin(roundf(maxy / 5), roundf(maxx / 8), roundf(maxy / 5 * 4), 0);
	my_wins[6] = newwin(roundf(maxy / 5), roundf(maxx / 8 * 6), roundf(maxy / 5 * 4), roundf(maxx / 8));
	my_wins[7] = newwin(roundf(maxy / 5), roundf(maxx / 8), roundf(maxy / 5 * 4), roundf(maxx / 8 * 7));

	for (int i = 0; i < 8; ++i)
		box(my_wins[i], 0, 0);
	for (int i = 0; i < 8; ++i)
		wrefresh(my_wins[i]);

	getch();
	endwin();
	return 0;
}
