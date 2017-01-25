#include "header.h"

int parse_ch (short ch)
{
	if (ch == KEY_BACKSPACE || ch == '\b' || ch == 127) {
		if (my_msgP == my_msgEP && my_msgP > my_msg) {
			--my_msgEP;
			--my_msgP;
			if (*my_msgP >= 128) {
				--my_msgP;
				--my_msgEP;
			}
		} else if (my_msgP < my_msgEP && my_msgP > my_msg) {
			if (*(my_msgP - 1) >= 128) {
				for (unsigned char *i = my_msgP - 1; i < my_msgEP; ++i)
					*i = *(i + 1);
				--my_msgP;
				--my_msgEP;
			}
			for (unsigned char *i = my_msgP - 1; i < my_msgEP; ++i)
				*i = *(i + 1);
			--my_msgP;
			--my_msgEP;
		}
		update_msgbox();
	} else if (ch >= 32) {
		if (my_msgP == my_msgEP) {
			*my_msgP = ch;
			++my_msgP;
			++my_msgEP;
		} else {
			for (unsigned char *i = my_msgEP; i > my_msgP; --i)
				*i = *(i - 1);
			*my_msgP = ch;
			++my_msgP;
			++my_msgEP;
		}
		update_msgbox();
	} else if (ch == '\n') {
		if (my_msgP == my_msgEP) {
			*my_msgP = ch;
			++my_msgP;
			++my_msgEP;
		} else {
			for (unsigned char *i = my_msgEP; i > my_msgP; --i)
				*i = *(i - 1);
			*my_msgP = ch;
			++my_msgP;
			++my_msgEP;
		}
		update_msgbox();
		getyx(stdscr, curY, curX);
		if (curY >= msgbox.ey)
			++msgoffset;
		update_msgbox();
	}
	return 0;
}
