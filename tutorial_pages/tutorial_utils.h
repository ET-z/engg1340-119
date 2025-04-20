#ifndef TUTORIAL_UTILS_H
#define TUTORIAL_UTILS_H

#include <string>
#include <cwchar>
#include <locale.h>
#include <unistd.h>
#include <ncursesw/ncurses.h>

// Animated print for narrow string (ASCII only)
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

// Animated print for wide string (Unicode + emoji)
inline void print_animated_w(WINDOW *win, int y, const std::wstring &text, int delay = 8000) {
    int x = 4;  // left padding; you can center if needed
    wattron(win, COLOR_PAIR(3));
    for (wchar_t ch : text) {
        mvwaddnwstr(win, y, x++, &ch, 1);
        wrefresh(win);
        usleep(delay);
    }
    wattroff(win, COLOR_PAIR(3));
}

#endif
