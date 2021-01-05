#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#include <ncurses.h>
#include <pcre2.h>
#include <string.h>
#include <locale.h>
#include "config.h"

#define DX 3
#define ONLELINE 3
#define MAXSTR 80

void matching(char *inA, char *inB, WINDOW *win)
{
	pcre2_code *re;
    PCRE2_SPTR pattern;     /* PCRE2_SPTR is a pointer to unsigned code units of */
    PCRE2_SPTR subject;     /* the appropriate width (in this case, 8 bits). */

    int errnum;
    int rc;

    PCRE2_SIZE erroffs;
    PCRE2_SIZE *ovector;
    PCRE2_SIZE subject_length;

    pcre2_match_data *match_data;

	pattern = (PCRE2_SPTR)inA;
    subject = (PCRE2_SPTR)inB;
    subject_length = (PCRE2_SIZE)strlen((char *)subject);

	wprintw(win, "\n \'%s\' : \'%s\'\n", inA, inB);

#ifdef UTF
    re = pcre2_compile_8(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
#else
	re = pcre2_compile_8(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroffs, NULL);
#endif

	if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message_8(errnum, buffer, sizeof(buffer));
        wprintw(win, " PCRE2 compilation failed at offset %d: %s\n", (int)erroffs,
               buffer);
        return;
    }

	match_data = pcre2_match_data_create_from_pattern_8(re, NULL);

    rc = pcre2_match_8(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        switch(rc) {
        case PCRE2_ERROR_NOMATCH:
            wprintw(win, " No match\n");
            break;
        default:
            wprintw(win, " Matching error %d\n", rc);
            break;
        }
        pcre2_match_data_free_8(match_data);   /* Release memory used for the match */
        pcre2_code_free_8(re);                 /*   data and the compiled pattern. */
        return;
    }

	ovector = pcre2_get_ovector_pointer_8(match_data);

    for (int i = 0; i < rc; i++)
	{
        wprintw(win, " %2ld: %.*s\n", ovector[2*i],
			     (int)(ovector[2*i+1] - ovector[2*i]),
			     subject + ovector[2*i]);
	}

    pcre2_match_data_free_8(match_data);  /* Release the memory that was used */
    pcre2_code_free_8(re);                /* for the match data and the pattern. */

}


void main() {
	WINDOW *winA, *winB, *winO;
	char inA[MAXSTR], inB[MAXSTR];
	int c = 0;
	int half;

	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	printw("Input:");
	refresh();


	half = (COLS-2*DX)/2;
	winA = newwin(ONLELINE, half, DX, DX);
	winB = newwin(ONLELINE, half, DX, DX+half);
	winO = newwin(LINES-ONLELINE-DX*2, (COLS-2*DX), DX+ONLELINE, DX);
	keypad(winA, TRUE);
	keypad(winB, TRUE);
	scrollok (winO, TRUE);
	box(winA, 0, 0);
	box(winB, 0, 0);
	box(winO, 0, 0);
	box(winA, 0, 0);
	wrefresh(winA);
	wrefresh(winB);
	wrefresh(winO);
	wmove(winO, 1, 0);
	do {
		werase(winA); werase(winB);
		box(winA, 0, 0); wrefresh(winA);
		box(winB, 0, 0); wrefresh(winB);
		mvwgetnstr(winA, 1, 1, inA, MAXSTR);
		mvwgetnstr(winB, 1, 1, inB, MAXSTR);
		matching(inA, inB, winO);
		box(winO, 0, 0);
		wrefresh(winO);
	} while(*inA);

	endwin();

}
