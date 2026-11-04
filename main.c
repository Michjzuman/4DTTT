#include <stdio.h>
#include <unistd.h>

#include "bots.h"

const char symbols[] = {' ', 'X', 'O', '*', '#'};

U0 draw(Game *game, GameResult result) {
    system("clear");
    if (game->d == 2) {
        for (U8 y = 0; y < SIZE; y++) {
            for (U8 x = 0; x < SIZE; x++) {
                printf("%c", symbols[game->board[get_field(2, (U8[]){x, y})]]);
                printf(x == SIZE - 1 ? "\n" : " ");
            }
        }
    } else if (game->d == 3) {
        for (U8 z = 0; z < SIZE; z++) {
            for (U8 y = 0; y < SIZE; y++) {
                for (U8 x = 0; x < SIZE; x++) {
                    U64 field = get_field(3, (U8[]){x, y, z});
                    Bool win = FALSE;
                    if (result.winner != 0) {
                        for (U8 i = 0; i < SIZE; i++) {
                            win |= result.line[i] == field;
                        }
                    }
                    if (win) printf("\033[33m");
                    printf("%c", symbols[game->board[field]]);
                    if (win) printf("\033[0m");
                    printf(x == SIZE - 1 ? "\n" : " ");
                }
            }
            printf(z == SIZE - 1 ? "" : "-----\n");
        }
        printf("=====\n");
    } else if (game->d == 4) {
        for (U8 z = 0; z < SIZE; z++) {
            for (U8 y = 0; y < SIZE; y++) {
                for (U8 m = 0; m < SIZE; m++) {
                    for (U8 x = 0; x < SIZE; x++) {
                        U64 field = get_field(4, (U8[]){x, y, z, m});
                        Bool win = FALSE;
                        if (result.winner != 0) {
                            for (U8 i = 0; i < SIZE; i++) {
                                win |= result.line[i] == field;
                            }
                        }
                        if (win) printf("\033[33m");
                        printf("%c", symbols[game->board[field]]);
                        if (win) printf("\033[0m");
                        printf(" ");
                    }
                    printf(m == SIZE - 1 ? "\n" : "| ");
                }
            }
            if (z < SIZE - 1) for (U8 y = 0; y < SIZE; y++) {
                printf("------");
                printf(y == SIZE - 1 ? "\n" : "+-");
            }
        }
        printf("=====\n");
    }
    usleep(10000);
}

I32 main(U0) {
    play(4, draw, (Player[]){
        {jonkler, NULL}, {jonkler, NULL},
        {jonkler, NULL}, {jonkler, NULL}
    });
    return 0;
}