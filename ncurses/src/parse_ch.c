#include "header.h"

/* handle symbol */
int parse_ch (short ch)
{
	if (ch == KEY_BACKSPACE || ch == '\b' || ch == 127) {     /* \b, 127, KEY_BACKSPACE are       */
        /* if cursor is on end of message, remove 1 symbol */ /* different encodings of backspace */
		if (my_msgP == my_msgEP && my_msgP > my_msg) {    
			--my_msgEP;
			--my_msgP;
			if (*my_msgP >= 128) { /* for russian symbols */
				--my_msgP;
				--my_msgEP;
			}
		/* else shift all message after given symbol on 1 position to left */
		} else if (my_msgP < my_msgEP && my_msgP > my_msg) {
			/* for russian symbols */
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
	/* handler for normal symbols, not backspace */
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
