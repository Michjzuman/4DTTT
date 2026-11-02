#ifndef _4DTTT_H
#define _4DTTT_H

#include "utils.h"

#define SIZE 3

typedef struct {
    U8 amount_of_players;
    U8 turn;
    U8 d;
    U8 *board;
} Game;

typedef U0(*VF)(Game *);
typedef U64(*PF)(Game *, U0 *);

typedef struct {
    PF function;
    U0 *args;
} Player;

Game init_game(U8 d);
U0 close_game(Game *);

U64 get_field(U8 d, U8 *position);

Bool validate_move(Game *game, U64 move);
U0 do_move(Game *, U64 move, U8 player);

U8 get_winner(Game *);

U8 play(U8 d, VF vis, Player *players);

U0 bg(Game *);

#endif