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

typedef struct {
    U8 winner;
    U64 line[SIZE];
} GameResult;

typedef U0(*VF)(Game *, GameResult);
typedef U64(*PF)(Game *, U0 *);

typedef struct {
    PF function;
    U0 *args;
} Player;

typedef struct {
    U8 value;
    U64 field;
} MetaField;

Game init_game(U8 d);
U0 close_game(Game *);

U64 get_field(U8 d, U8 *position);
MetaField *get_metaboard(Game *);

Bool validate_move(Game *, U64 move);
U0 do_move(Game *, U64 move, U8 player);

GameResult get_winner(U8 d, Game *);

GameResult play(U8 d, VF vis, Player *players);

U0 bg(Game *, GameResult);

#endif