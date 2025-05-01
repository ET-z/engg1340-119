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

int tutorial3(WINDOW *game_win)
{
    int HEIGHT, WIDTH;
    getmaxyx(game_win, HEIGHT, WIDTH);

    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // Optional
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Titles
    init_pair(3, COLOR_WHITE, COLOR_BLACK);  // Body

    int ch;
    while (true)
    {
        werase(game_win);
        box(game_win, 0, 0);

        // Title
        wattron(game_win, A_BOLD | COLOR_PAIR(2));
        print_animated_w(game_win, 2, L"About the Dealer (AI):");
        wattroff(game_win, A_BOLD | COLOR_PAIR(2));

        // Dealer info
        int y = 4;
        std::vector<std::wstring> dealer_lines = {
            L"- The dealer will always shoot at you on their turn.",
            L"- You can disrupt their turn using items like Handcuffs.",
        };
        wattron(game_win, COLOR_PAIR(3));
        for (const auto &line : dealer_lines)
        {
            print_animated_w(game_win, y++, line);
        }
        wattroff(game_win, COLOR_PAIR(3));

        // ❤️ Health Info
        y += 1;
        wattron(game_win, A_BOLD | COLOR_PAIR(2));
        print_animated_w(game_win, y++, L"Health Info ❤️:");
        wattroff(game_win, A_BOLD | COLOR_PAIR(2));

        std::vector<std::wstring> health_lines = {
            L"- You and the dealer start at 60 HP.",
            L"- A live round deals 20 damage.",
            L"- Reduce the dealer’s HP to 0 to win.",
        };
        wattron(game_win, COLOR_PAIR(3));
        for (const auto &line : health_lines)
        {
            print_animated_w(game_win, y++, line);
        }
        wattroff(game_win, COLOR_PAIR(3));

        // ⏸ Pause & Exit
        y += 1;
        wattron(game_win, A_BOLD | COLOR_PAIR(2));
        print_animated_w(game_win, y++, L"⏸ Pause & Exit:");
        wattroff(game_win, A_BOLD | COLOR_PAIR(2));

        std::vector<std::wstring> pause_lines = {
            L"- ESC → Pause the game",
            L"- M → Return to Main Menu",
            L"- Q → Quit"};
        wattron(game_win, COLOR_PAIR(3));
        for (const auto &line : pause_lines)
        {
            print_animated_w(game_win, y++, line);
        }
        wattroff(game_win, COLOR_PAIR(3));

        // Final line
        y += 1;
        wattron(game_win, A_BOLD | COLOR_PAIR(3));
        print_animated_w(game_win, y++, L"Good luck. Outplay the dealer.");
        wattroff(game_win, A_BOLD | COLOR_PAIR(3));

        // Navigation footer
        y += 2;
        wattron(game_win, A_BOLD | COLOR_PAIR(3));
        print_animated_w(game_win, y++, L"⬅️ Back  |  ESC to exit");
        wattroff(game_win, A_BOLD | COLOR_PAIR(3));

        wrefresh(game_win);

        ch = wgetch(game_win);
        if (ch == KEY_LEFT)
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
