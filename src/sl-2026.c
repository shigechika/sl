/*
 * sl-2026 - Steam Locomotive with conditional sweep
 *
 * Based on sl-2023. Reads SL_SWEEP_COL from the environment to determine
 * when to start sweeping (deleting characters at the left edge).
 * Without SL_SWEEP_COL, sweeps only at x=0 (last frame).
 */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <term.h>

void mvprintw(int y, int x, const char* fmt, const char* str) {
    tputs(tparm(tgoto(cursor_address, x, y)), 1, putchar);
    printf(fmt, str);
}

/* Trailing spaces on body lines erase remnants when not sweeping.
   Smoke line gets " o" appended each frame so it self-extends. */
char *sl[] = {
    "      o o o o o",
    "     o         ",
    "    o  ┯━━┯    ",
    "   ╒╕  │OO│    ",
    " ┌─┘└──┘  │    ",
    "┌┘        │    ",
    "┴─O=O O=O─┴ з  \n"
};

int main() {
    setupterm(NULL, STDOUT_FILENO, NULL);
    int COLS = tigetnum("cols"), LINES = tigetnum("lines");
    int len = strlen(sl[0]), height = sizeof(sl)/sizeof(sl[0]);
    int start_x = COLS - len, start_y = LINES - height - 1;
    char dch2[20] = "", *dch2p = tparm(tigetstr("dch"), 2);
    if (dch2p != NULL)
        strcpy(dch2, dch2p);
    char *env = getenv("SL_SWEEP_COL");
    int clear_col = (env && *env) ? atoi(env) : 0;
    char smoke[1024]; strcpy(smoke, sl[0]); sl[0] = smoke;
    for (int x = start_x/2*2; x >= 0; x -= 2) {
        for (int y = 0; y < height; y++) {
            if (x <= clear_col)
                mvprintw(start_y + y, 0, "%s", dch2);
            mvprintw(start_y + y, x, "%s", sl[y]);
        }
        fflush(stdout);
        strcat(smoke, " o");
        usleep(100000);
    }
}
