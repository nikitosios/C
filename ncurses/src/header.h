#ifndef HEADER_H
#define HEADER_H
#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>

#define BORD_WIDTH 7
#define MSG_SIZE 2022

#if defined(_WIN32) || defined(_WIN64)
#include <window.h>
#define msleep(msec) Sleep(msec)
#else
#include <unistd.h>
#define msleep(msec) usleep(msec*1000)
#endif

#define true 1
#define false 0
#define MSGEND 1
#define STREND 0

struct object create_object (int y, int x, int h, int w, unsigned int flags, bool form);
int update_screen (void);
int update_msgbox (void);
int send_message (unsigned char *msg);
int show_messages (void);
char *msgformat (unsigned char *msg);
int parse_ch (short ch);
int msggetstrn (unsigned char *pointer);
int msggetsymn (void);
int msggo (int y, int x);

typedef struct object {
	int y, x, h, w, ey, ex, cy, cx;
	WINDOW *win;
} object;

extern struct object msgsend;
extern struct object msgbox;
extern struct object filesend;
extern struct object alarm_b;
extern struct object my_msgs;
extern struct object his_msgs;

extern bool alarming;
extern unsigned char my_msg[MSG_SIZE];
extern unsigned char *my_msgP;
extern unsigned char *my_msgEP;
extern int msgoffset;
extern int curY, curX;
extern FILE *history;
#endif
