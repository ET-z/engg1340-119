#include <iostream>
#include <vector>
#include <string>
#include <locale.h>
#include <cwchar>             // for wide strings
#include <unistd.h>           // for usleep
#include <ncursesw/ncurses.h> // wide-character ncurses
#include "../game.h"
#include "tutorial_utils.h"

int tutorial1(WINDOW *game_win)
{
    setlocale(LC_ALL, ""); // use for emoji

    int HEIGHT, WIDTH;
    getmaxyx(game_win, HEIGHT, WIDTH);

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Title
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // Body

    int ch;

    std::vector<std::wstring> lines = {
        L"🎮 Buckshot Roulette: Tutorial",
        L"",
        L"Welcome to Buckshot Roulette.",
        L"A psychological shootout between you and the dealer.",
        L"Your life depends on a chambered round.",
        L"",
        L"You’ll take turns with the dealer — spin the cylinder and pull the trigger.",
        L"Each round could be a blank... or a live shot.",
        L"",
        L"🎯 Goal: Survive and outlast the dealer.",
        L"Each shootout has 9 rounds. If one of you reaches 0 HP, game over."};

    // Menu loop
    while (true)
    {
        wclear(game_win);
        box(game_win, 0, 0);

        int line_y = 2;
        for (size_t i = 0; i < lines.size(); ++i)
        {
            int x = (WIDTH - lines[i].length()) / 2;

            // Title gets a special color
            if (i == 0)
            {
                wattron(game_win, COLOR_PAIR(1) | A_BOLD);
            }
            else
            {
                wattron(game_win, COLOR_PAIR(2) | A_BOLD);
            }

            mvwaddwstr(game_win, line_y, x, lines[i].c_str());

            if (i == 0)
            {
                wattroff(game_win, COLOR_PAIR(1) | A_BOLD);
            }
            else
            {
                wattroff(game_win, COLOR_PAIR(2) | A_BOLD);
            }

            line_y += 2;
            wrefresh(game_win);
            usleep(100000); // 100ms delay for animation
        }

        // Navigation arrow and escape message
        wattron(game_win, A_BOLD | COLOR_PAIR(3));
        print_animated_w(game_win, line_y++, L"ESC to exit  |  Continue ➡️");
        wattroff(game_win, A_BOLD | COLOR_PAIR(3));

        wrefresh(game_win);

        ch = wgetch(game_win);
        if (ch == KEY_RIGHT)
        {
            tutorial2(game_win);
            break;
        }
        else if (ch == 27)
        {
            return 1;
        }
    }

    return 0;
}
