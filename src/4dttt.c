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

Game copy_game(Game *src) {
    Game game = *src;
    U64 size = power(SIZE, src->d);
    game.board = malloc(size);
    memcpy(game.board, src->board, size);
    return game;
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
    if (move >= power(SIZE, game->d)) return FALSE;
    return game->board[move] == 0;
}

U0 do_move(Game *game, U64 move, U8 player) {
    game->board[move] = player + 1;
}

MetaField *get_metaboard(Game *game) {
    U64 size = power(SIZE, game->d);
    MetaField *mb = malloc(size * sizeof(MetaField));
    for (U64 i = 0; i < size; i++) {
        mb[i] = (MetaField){
            .value = game->board[i],
            .field = i
        };
    }
    return mb;
}

GameResult get_winner_recursion(U8 d, MetaField *mb) {
    if (d == 1) {
        if (mb[0].value != 0) {
            Bool is_win = TRUE;
            for (U8 i = 1; i < SIZE; i++) {
                if (mb[0].value != mb[i].value) {
                    is_win = FALSE;
                    break;
                }
            }
            if (is_win) {
                GameResult result;
                result.winner = mb[0].value;
                for (U8 i = 0; i < SIZE; i++) {
                    result.line[i] = mb[i].field;
                }
                return result;
            }
        }
    } else if (d >= 2) {
        U64 x = 0, y = 0;
        /*
        if (d == 3) {
            U64 size = power(SIZE, d);
            Game g = init_game(4);
            for (U64 i = 0; i < size; i++) {
                printf("%llu", mb[i].field);
                printf(i == size - 1 ? "\n" : ", ");
                do_move(&g, mb[i].field, 0);
            }
            U0 draw(Game *, GameResult);
            draw(&g, (GameResult){0});
        }
        */
        U64 next_layer = power(SIZE, d - 1);
        U64 piece_size = power(SIZE, d - 2);
        for (U8 i = 0; i < SIZE; i++) {
            {
                GameResult r = get_winner_recursion(d - 1, &mb[y]);
                if (r.winner != 0) return r;
                y += next_layer;
            }
            {
                MetaField b[next_layer];
                for (U8 i1 = 0; i1 < SIZE; i1++) {
                    memcpy(
                        &b[i1 * piece_size],
                        &mb[x + i1 * next_layer],
                        piece_size * sizeof(MetaField)
                    );
                }
                GameResult r = get_winner_recursion(d - 1, b);
                if (r.winner != 0) return r;
                x += piece_size;
            }
        }
        {
            MetaField b[next_layer];
            for (U8 i1 = 0; i1 < SIZE; i1++) {
                memcpy(
                    &b[i1 * piece_size],
                    &mb[i1 * (next_layer + piece_size)],
                    piece_size * sizeof(MetaField)
                );
            }
            GameResult r = get_winner_recursion(d - 1, b);
            if (r.winner != 0) return r;
        }
        {
            MetaField b[next_layer];
            for (U8 i1 = 0; i1 < SIZE; i1++) {
                memcpy(
                    &b[i1 * piece_size],
                    &mb[(next_layer - piece_size) + i1 * (next_layer - piece_size)],
                    piece_size * sizeof(MetaField)
                );
            }
            GameResult r = get_winner_recursion(d - 1, b);
            if (r.winner != 0) return r;
        }
    }
    return (GameResult){0};
}

GameResult get_winner(U8 d, Game *game) {
    MetaField *mb = get_metaboard(game);
    GameResult result = get_winner_recursion(game->d, mb);
    free(mb);
    return result;
}

U0 bg(Game *g, GameResult r) {}

GameResult play(U8 d, VF vis, Player *players) {
    Game game = init_game(d);
    GameResult result = {0};
    do {
        vis(&game, result);
        {
            Player p = players[game.turn];
            Game check_game = copy_game(&game);
            U64 move = p.function(&check_game, p.args);
            close_game(&check_game);
            if (validate_move(&game, move)) {
                do_move(&game, move, game.turn);
            }
        }
        game.turn++;
        game.turn %= game.amount_of_players;
        result = get_winner(game.d, &game);
    } while (result.winner == 0);
    vis(&game, result);
    close_game(&game);
    return result;
}
