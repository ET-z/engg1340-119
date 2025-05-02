#include <iostream>
#include <vector>
#include <string>
#include <locale.h>
#include <cwchar>
#include <unistd.h>
#include <ncursesw/ncurses.h>
#include "../game.h"
#include "tutorial_utils.h"

using namespace std;

int tutorial2(WINDOW *game_win)
{
    setlocale(LC_ALL, "");
    int HEIGHT, WIDTH;
    getmaxyx(game_win, HEIGHT, WIDTH);
    start_color();

    // Color pairs
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // (Optional)
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Titles
    init_pair(3, COLOR_WHITE, COLOR_BLACK);  // Body

    int ch;
    while (true)
    {
        werase(game_win);
        box(game_win, 0, 0);

        // 🟡 Title: Your Moves
        wattron(game_win, A_BOLD | COLOR_PAIR(2));
        print_animated_w(game_win, 2, L"📄 Your Moves:");
        wattroff(game_win, A_BOLD | COLOR_PAIR(2));

        // 🤍 Body text: Moves
        int y = 4;
        vector<wstring> lines = {
            L"- e → Use an item ✍️",
            L"- ENTER or SPACE → Initiate an action (1 or 2) ✅",
            L"- 1 → Shoot yourself 💥",
            L"- 2 → Shoot the dealer 🎯",
            L"- Arrow keys → Navigate inventory ↕️",
        };
        wattron(game_win, COLOR_PAIR(3));
        for (const auto &line : lines)
        {
            print_animated_w(game_win, y++, line);
        }
        wattroff(game_win, COLOR_PAIR(3));

        // 🟡 Title: Items
        y += 1;
        wattron(game_win, A_BOLD | COLOR_PAIR(2));
        print_animated_w(game_win, y++, L"📦 Items:");
        wattroff(game_win, A_BOLD | COLOR_PAIR(2));

        // 🤍 Body text: Items
        vector<wstring> items = {
            L"- Apple → +20 HP 🍎",
            L"- Knife → Double your damage🔪",
            L"- Beer → Discard the current shell 🍺",
            L"- Magnifying Glass → See if the next shell is live 🔎",
            L"- Handcuff → Skip the dealer's turn ⛓️",
            L"- To pick up item: press E/e"};
        wattron(game_win, COLOR_PAIR(3));
        for (const auto &item : items)
        {
            print_animated_w(game_win, y++, item);
        }
        wattroff(game_win, COLOR_PAIR(3));

        // Navigation
        y += 2;
        wattron(game_win, A_BOLD | COLOR_PAIR(3));
        print_animated_w(game_win, y++, L"⬅️ Back  |  ESC to exit  |  Continue ➡️");
        wattroff(game_win, A_BOLD | COLOR_PAIR(3));

        wrefresh(game_win);
        ch = wgetch(game_win);

        if (ch == KEY_RIGHT)
        {
            tutorial3(game_win);
            break;
        }
        else if (ch == KEY_LEFT)
        {
            tutorial1(game_win);
            break;
        }
        else if (ch == 27)
        { // ESC
            return 1;
        }
    }

    return 0;
}
