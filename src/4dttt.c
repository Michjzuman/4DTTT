#include <stdio.h>
#include <string.h>

#include "4dttt.h"

Game init_game(U8 d) {
    Game r = {
        .amount_of_players = d, .d = d,
        .board = calloc(power(SIZE, d), 1),
        .turn = 0
    };
    return r;
}

U0 close_game(Game *game) {
    free(game->board);
}

U64 get_field(U8 d, U8 *position) {
    U64 i = 0;
    for (U8 di = 0; di < d; di++) {
        i += power(SIZE, di) * position[di];
    }
    return i;
}

Bool validate_move(Game *game, U64 move) {
    return game->board[move] == 0;
}

U0 do_move(Game *game, U64 move, U8 player) {
    U8 *field = &game->board[move];
    if (validate_move(game, move)) *field = player;
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

U0 bg(Game *g) {}

U8 play(U8 d, VF vis, Player *players) {
    Game game;
    U8 winner = 0;
    do {
        vis(&game);
        {
            Player p = players[game.turn];
            U64 move = p.function(&game, p.args);
            if (validate_move(&game, move)) {
                do_move(&game, move, game.turn);
            }
        }
        game.turn++;
        game.turn %= game.amount_of_players;
        winner = get_winner(&game);
    } while (winner == 0);
    vis(&game);
    return 0;
}
