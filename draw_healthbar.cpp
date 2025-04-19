#include <ncurses.h>
#include "draw_healthbar.h"

void healthbar(WINDOW *bar_win, int health) {
    werase(bar_win);
    box(bar_win, 0, 0);

    int maxWidth = getmaxx(bar_win) - 2;
    int fill = (health * maxWidth) / 100;

    // Define a color pair for green fill (once per game session)
    static bool color_initialized = false;
    if (!color_initialized) {
        init_pair(3, COLOR_GREEN, COLOR_BLACK); // Pair 3 = green text on black
        color_initialized = true;
    }

    // Draw the filled portion
    wattron(bar_win, COLOR_PAIR(3));
    for (int i = 0; i < fill; ++i) {
        mvwaddch(bar_win, 1, i + 1, ACS_CKBOARD); // Fill char
    }
    wattroff(bar_win, COLOR_PAIR(3));

    // show % value
    mvwprintw(bar_win, 1, (maxWidth / 2) - 3, "%3d%%", health);

    wrefresh(bar_win);
}
