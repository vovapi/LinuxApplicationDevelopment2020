#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

int min(int a, int b) {
    if (a<b) {
        return a;
    }
    return b;
}
int main(int argc, char** argv) {
    if (argc < 2) {
        // TODO: error message
        return 1;
    }
    WINDOW *win, *inside;
    int c = 0;

    initscr();
    noecho();
    cbreak();
    printw(argv[1]);
    refresh();

    win = newwin(LINES-1, COLS, 1, 0);
    keypad(win, TRUE);
    box(win, 0, 0);
    // wrefresh(win);
    inside = derwin(win, LINES - 3, COLS-2, 1, 1);
    scrollok (inside, TRUE);
    FILE* f = fopen(argv[1], "r");
    char * line = (char *)calloc((COLS-2),sizeof(char));
    size_t size = COLS-2;
    ssize_t n = -1;
        int done = 0;
    for (int i = 0; (i < LINES-4) && !done; i++) {
        n = getline(&line, &size, f);
        if (n == -1) {
            done = 1;
        } else {
            waddnstr(inside, line, min(n-1, COLS-3));
            waddch(inside, '\n');
            wrefresh(win);
        }
    }
    while ((c = wgetch(inside)) != 27) {
        if (done) {
            beep();
        }
        switch (c) {
            case 32: // SPACE
                n = getline(&line, &size, f);
                if (n == -1) {
                    done = 1;
                } else {
                    waddnstr(inside, line, min(n-1, COLS-3));
                    waddch(inside, '\n');
                    wrefresh(win);
                }

                break;
        }
    }
    fclose(f);
    delwin(inside);
    delwin(win);
    endwin();
    return 0;
}
