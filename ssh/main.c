#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

int main()
{
	ssh_session my_ssh_session;
	ssh_channel channel;
	int ch, rc;
	char *password, *hostname = "localhost";
	char *command1 = "echo command1 >> logfile", *command2 = "echo command2 >> logfile";
	MEVENT event;
	WINDOW *button;

	/* open session and set options */
	my_ssh_session = ssh_new();
	if (my_ssh_session == NULL)
		return -1;
	ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, hostname);

	/* connect to server */
	rc = ssh_connect(my_ssh_session);
	if (rc != SSH_OK)
	{
		fprintf(stderr, "Error connecting to %s: %s\n", hostname,
				ssh_get_error(my_ssh_session));
		ssh_free(my_ssh_session);
		return -1;
	}

	/* authenticate ourselves */
	password = getpass("Password: ");
	rc = ssh_userauth_password(my_ssh_session, NULL, password);
	if (rc != SSH_AUTH_SUCCESS)
	{
		fprintf(stderr, "Error authenticating with password: %s\n",
				ssh_get_error(my_ssh_session));
		ssh_disconnect(my_ssh_session);
		ssh_free(my_ssh_session);
		return -1;
	}

	channel = ssh_channel_new(my_ssh_session);
	if (channel == NULL)
		return SSH_ERROR;

	rc = ssh_channel_open_session(channel);
	if (rc != SSH_OK)
	{
		ssh_channel_free(channel);
		return rc;
	}

	initscr();
	noecho();
	cbreak();
	start_color();
	curs_set(0);
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS, NULL);

	init_pair(1, COLOR_BLACK, COLOR_CYAN);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_BLACK, COLOR_RED);

	bkgd(COLOR_PAIR(1));
	clear();
	refresh();
	button = newwin(LINES / 2, COLS / 2, LINES / 4, COLS / 4);
	wbkgd(button, COLOR_PAIR(2));
	wclear(button);
	box(button, '|', '-');
	wrefresh(button);

	while (1)
	{
		ch = getch();

		switch (ch)
		{
			case KEY_MOUSE:
			if (getmouse(&event) == OK)
			{
				if (event.x >= COLS / 4 && event.x <= COLS / 4 * 3 && event.y <= LINES / 4 * 3
						&& event.y >= LINES / 4 && event.bstate & BUTTON1_PRESSED)
				{
					rc = ssh_channel_request_exec(channel, command1);
					wbkgd(button, COLOR_PAIR(3));
					wclear(button);
					box(button, '|', '-');
					wrefresh(button);
				} else if (event.bstate & BUTTON1_RELEASED)
				{
					printw("released");
					rc = ssh_channel_request_exec(channel, command2);
					wbkgd(button, COLOR_PAIR(2));
					wclear(button);
					box(button, '|', '-');
					wrefresh(button);
				}
			}
			break;
		}
	}

	endwin();

	ssh_channel_send_eof(channel);
	ssh_channel_close(channel);
	ssh_channel_free(channel);

	ssh_disconnect(my_ssh_session);
	ssh_free(my_ssh_session);

	return SSH_OK;
}
