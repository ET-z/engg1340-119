#ifndef TUTORIAL_UTILS_H
#define TUTORIAL_UTILS_H

#include <string>
#include <ncurses.h>
#include <unistd.h>

// This ensures one definition per translation unit
inline void print_animated(WINDOW *win, int y, const std::string &text, int delay = 20000) {
    int x = (getmaxx(win) - static_cast<int>(text.length())) / 2;
    wattron(win, COLOR_PAIR(3));
    for (size_t i = 0; i < text.length(); ++i) {
        mvwaddch(win, y, x + i, text[i]);
        wrefresh(win);
        usleep(delay);
    }
    wattroff(win, COLOR_PAIR(3));
}

#endif
