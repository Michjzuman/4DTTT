#include <stdio.h>

#include "4dttt.h"

U0 draw(Game *game) {
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
    }
}

I32 main(U0) {
    Game game = init_game(3);

    do_move(&game, get_field(game.d, (U8[]){2, 0, 0}), 1);
    do_move(&game, get_field(game.d, (U8[]){1, 0, 1}), 1);
    do_move(&game, get_field(game.d, (U8[]){0, 0, 2}), 1);

    draw(&game);
    printf("winner: %u\n", get_winner(&game));
    
    return 0;
}