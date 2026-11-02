#include <stdlib.h>

#include "4dttt.h"

U64 jonkler(Game *game, U0 *args) {
    U64 move;
    do {
        for (U8 i = 0; i < sizeof(U64); i++) {
            move |= i * 8;
        }
    } while (validate_move(game, move));
    return move;
}
