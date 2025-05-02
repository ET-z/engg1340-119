#ifndef TUTORIAL_UTILS_H
#define TUTORIAL_UTILS_H

#include <string>
#include <cwchar>
#include <locale.h>
#include <unistd.h>
#include <ncursesw/ncurses.h>
#include <wchar.h>

// Animated print for wide string (Unicode + emoji)
inline void print_animated_w(WINDOW *win, int y, const std::wstring &text, int delay = 8000)
{
    int x = (getmaxx(win) - wcswidth(text.c_str(), text.length())) / 2;
    wattron(win, COLOR_PAIR(3));
    for (wchar_t ch : text)
    {
        mvwaddnwstr(win, y, x++, &ch, 1);
        wrefresh(win);
        usleep(delay);
    }
    wattroff(win, COLOR_PAIR(3));
}

#endif
