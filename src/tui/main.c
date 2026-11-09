#include "bots.h"
#include "tui.h"

I32 main(U0) {
    init_tui();

    play(4, tui, (Player[]) {
        {jonkler, NULL},
        {jonkler, NULL},
        {jonkler, NULL},
        {jonkler, NULL},
        {jonkler, NULL},
        {jonkler, NULL}
    });

    close_tui();
    return 0;
}

