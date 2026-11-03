#include <stdlib.h>

#include "4dttt.h"

U64 jonkler(Game *game, U0 *args) {
    U64 move;
    do {
        for (U8 i = 0; i < sizeof(U64); i++) {
            move |= (U8)rand()<<(i * 8);
        }
        move %= power(SIZE, game->d);
    } while (!validate_move(game, move));
    return move;
}
