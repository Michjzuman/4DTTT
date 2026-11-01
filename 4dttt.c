#include <stdio.h>
#include <string.h>

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

Game init_game(U8 d) {
    Game r = {
        .amount_of_players = d, .d = d,
        .board = calloc(power(SIZE, d), 1)
    };
    return r;
}

U8 *get_field(Game *game, U8 *position) {
    U64 i = 0;
    for (U8 d = 0; d < game->d; d++) {
        i += power(SIZE, d) * position[d];
    }
    return &game->board[i];
}

Bool do_move(Game *game, U8 *position, U8 player) {
    U8 *field = get_field(game, position);
    if (*field == 0) {
        *field = player; return TRUE;
    }
    return FALSE;
}

U8 get_winner(Game *game) {
    if (game->d == 1) {
        U8 *b = game->board;
        if (b[0] == b[1] && b[0] == b[2]) {
            return game->board[0];
        }
    } else if (game->d >= 2) {
        U64 x = 0, y = 0;
        U64 next_layer = power(SIZE, game->d - 1);
        for (U8 i = 0; i < SIZE; i++) {
            {
                U8 r = get_winner(&(Game){
                    .amount_of_players = game->amount_of_players,
                    .board = &game->board[y],
                    .d = game->d - 1
                });
                if (r != 0) return r;
                y += next_layer;
            }
            {
                U64 piece_size = power(SIZE, game->d - 2);
                U8 b[next_layer];
                for (U8 i1 = 0; i1 < SIZE; i1++) {
                    memcpy(
                        &b[i1 * piece_size],
                        &game->board[x + i1 * next_layer],
                        piece_size
                    );
                }
                U8 r = get_winner(&(Game){
                    .amount_of_players = game->amount_of_players,
                    .board = b,
                    .d = game->d - 1
                });
                if (r != 0) return r;
                x += piece_size;
            }
        }
        {
            U64 piece_size = power(SIZE, game->d - 2);
            {
                U8 b[next_layer];
                for (U8 i1 = 0; i1 < SIZE; i1++) {
                    memcpy(
                        &b[i1 * piece_size],
                        &game->board[i1 * (next_layer + piece_size)],
                        piece_size
                    );
                }
                U8 r = get_winner(&(Game){
                    .amount_of_players = game->amount_of_players,
                    .board = b,
                    .d = game->d - 1
                });
                if (r != 0) return r;
            }
            {
                U8 b[next_layer];
                for (U8 i1 = 0; i1 < SIZE; i1++) {
                    memcpy(
                        &b[i1 * piece_size],
                        &game->board[(SIZE - 1) + i1 * (next_layer - piece_size)],
                        piece_size
                    );
                }
                U8 r = get_winner(&(Game){
                    .amount_of_players = game->amount_of_players,
                    .board = b,
                    .d = game->d - 1
                });
                if (r != 0) return r;
            }
        }
    }
    return 0;
}

U0 draw2D(Game *game) {
    for (U8 y = 0; y < SIZE; y++) {
        for (U8 x = 0; x < SIZE; x++) {
            printf("%u", game->board[SIZE * y + x]);
            printf(x == SIZE - 1 ? "\n" : " ");
        }
    }
}

I32 main(U0) {
    {
        Game game = init_game(2);
        do_move(&game, (U8[]){2, 0}, 1);
        do_move(&game, (U8[]){2, 1}, 1);
        do_move(&game, (U8[]){2, 2}, 1);
        draw2D(&game);
        printf("winner: %u\n---\n", get_winner(&game));
    }
    {
        Game game = init_game(2);
        do_move(&game, (U8[]){0, 1}, 1);
        do_move(&game, (U8[]){1, 1}, 1);
        do_move(&game, (U8[]){2, 1}, 1);
        draw2D(&game);
        printf("winner: %u\n---\n", get_winner(&game));
    }
    {
        Game game = init_game(2);
        do_move(&game, (U8[]){0, 0}, 1);
        do_move(&game, (U8[]){1, 1}, 1);
        do_move(&game, (U8[]){2, 2}, 1);
        draw2D(&game);
        printf("winner: %u\n---\n", get_winner(&game));
    }
    {
        Game game = init_game(2);
        do_move(&game, (U8[]){2, 0}, 1);
        do_move(&game, (U8[]){1, 1}, 1);
        do_move(&game, (U8[]){0, 2}, 1);
        draw2D(&game);
        printf("winner: %u\n---\n", get_winner(&game));
    }
    {
        Game game = init_game(2);
        do_move(&game, (U8[]){2, 0}, 1);
        do_move(&game, (U8[]){1, 1}, 1);
        do_move(&game, (U8[]){0, 0}, 1);
        draw2D(&game);
        printf("winner: %u\n---\n", get_winner(&game));
    }
    return 0;
}

