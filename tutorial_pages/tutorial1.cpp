#include <iostream>
#include <vector>
#include <string>
#include <locale.h>
#include <cwchar>       // for wide strings
#include <unistd.h>     // for usleep
#include <ncursesw/ncurses.h> // wide-character ncurses
#include "../game.h"

int tutorial1(WINDOW *game_win)
{
    setlocale(LC_ALL, "");  // Important for Unicode/emoji

    int HEIGHT, WIDTH;
    getmaxyx(game_win, HEIGHT, WIDTH);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // Default (not used here)
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Title
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    
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
        L"Each shootout has 9 rounds. If one of you reaches 0 HP, game over."
    };

    // Menu loop
    while (true)
    {
        // Clear game window
        wclear(game_win);
        box(game_win, 0, 0);

        // Animate lines one by one
        for (size_t i = 0; i < lines.size(); ++i)
        {
            int x = (WIDTH - lines[i].length()) / 2;
            mvwaddwstr(game_win, 2 + i, x, lines[i].c_str());
            wrefresh(game_win);
            usleep(100000);  
        }

        std::wstring arrow = L"→";
        mvwaddwstr(game_win, HEIGHT / 2, WIDTH - 6, arrow.c_str());

        wrefresh(game_win);
        ch = wgetch(game_win);

        if (ch == KEY_RIGHT)
        {
            tutorial2(game_win);
            break;
        }
        else if (ch == 27) // ESC
        {
            return 1;
        }
    }

    return 0;
}
