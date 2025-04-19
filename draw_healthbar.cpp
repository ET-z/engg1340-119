#include <ncurses.h>
#include "draw_healthbar.h"

// Render a horizontal health bar inside the given window
void healthbar(WINDOW *bar_win, int health) {
    werase(bar_win); // Clear previous contents
    box(bar_win, 0, 0); // Draw box border

    int maxWidth = getmaxx(bar_win) - 2; // Width inside the border
    int fill = (health * maxWidth) / 100;

    for (int i = 0; i < fill; ++i) {
        mvwaddch(bar_win, 1, i + 1, ACS_CKBOARD);
    }

    // Optional: print percentage
    mvwprintw(bar_win, 1, (maxWidth / 2) - 3, "%3d%%", health);

    wrefresh(bar_win);
}
