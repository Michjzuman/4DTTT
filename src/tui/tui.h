#ifndef TUI_H
#define TUI_H

#include "4dttt.h"

U0 init_tui(U0);
U0 close_tui(U0);

U0 tui(Game *, GameResult);

U64 human(Game *, U0 *);

#endif
