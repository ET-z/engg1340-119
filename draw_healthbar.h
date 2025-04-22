#ifndef DRAW_HEALTHBAR_H
#define DRAW_HEALTHBAR_H

#include <ncurses.h>

// Draw a health bar in a window, based on health value (0 to 100)
void healthbar(WINDOW *bar_win, int health);

#endif
