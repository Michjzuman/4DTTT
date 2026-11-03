#include <stdio.h>
#include <unistd.h>

#include "bots.h"

U0 draw(Game *game) {
    system("clear");
    if (game->d == 2) {
        for (U8 y = 0; y < SIZE; y++) {
            for (U8 x = 0; x < SIZE; x++) {
                printf("%u", game->board[get_field(2, (U8[]){x, y})]);
                printf(x == SIZE - 1 ? "\n" : " ");
            }
        }
    } else if (game->d == 3) {
        for (U8 z = 0; z < SIZE; z++) {
            for (U8 y = 0; y < SIZE; y++) {
                for (U8 x = 0; x < SIZE; x++) {
                    printf("%u", game->board[get_field(3, (U8[]){x, y, z})]);
                    printf(x == SIZE - 1 ? "\n" : " ");
                }
            }
            printf(z == SIZE - 1 ? "" : "-----\n");
        }
        printf("=====\n");
    }
    sleep(1);
}

I32 main(U0) {
    printf("winner: %u\n", play(
        2, draw, (Player[]){
            {jonkler, NULL},
            {jonkler, NULL},
            {jonkler, NULL}
        }
    ));
    
    return 0;
}