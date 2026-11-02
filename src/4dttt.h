#ifndef _4DTTT_H
#define _4DTTT_H

#include "utils.h"

#define SIZE 3

typedef struct {
    U8 amount_of_players;
    U8 d;
    U8 *board;
} Game;

typedef U8(*VF)(Game *);
typedef U8(*PF)(Game *);

typedef struct {
    PF function;
    U8 *name;
} Player;

Game init_game(U8 d);
U0 close_game(Game *);

U8 *get_field(Game *, U8 *position);

Bool do_move(Game *, U8 *position, U8 player);

U8 get_winner(Game *);

#endif