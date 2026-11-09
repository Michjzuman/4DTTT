#include <unistd.h>

#include <ncurses.h>

#include "4dttt.h"

#define FPS 30

U0 init_tui(U0) {
    initscr();
    noecho();
    curs_set(0);
    /*
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    timeout(1000 / FPS);
    */
}

U0 close_tui(U0) {
    endwin();
    exit(0);
}

U0 tui(Game *game, GameResult result) {
    clear();
    for (U64 i = 0; i < power(SIZE, game->d); i++) {
        U64 x = 0;
        for (U8 d = 1; d <= game->d; d+=2) {
            x += i / power(SIZE, d - 1) * power(SIZE, d / 2);
            x %= power(SIZE, (d + 1) / 2);
        }
        /*
        for (U8 d = 1; d <= game->d; d+=2) {
            x += (i) / SIZE;
        }
        */
        x *= 4;
        x += 2;
        U64 y = 0;
        for (U8 d = 2; d <= game->d; d+=2) {
            y += i / power(SIZE, d - 1) * power(SIZE, (d - 1) / 2);
            y %= power(SIZE, d / 2);
        }
        y *= 2;
        y += 1;
        mvprintw(y, x, "%llu", i);
        mvprintw(y+1, x-1, "---+", i);
        mvprintw(y, x+2, "|", i);
        if (i == 0) {
            mvaddch(y, x-1, '[');
            mvaddch(y, x+1, ']');
        }
    }
    refresh();
    /*
    I32 ch = getch();
    if (ch == 'q') { endwin(); exit(0); }
    */
    usleep(1000000); endwin(); exit(0);
}

U64 human(Game *game, U0 *args) {
    return 0;
}

