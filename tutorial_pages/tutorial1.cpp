#include <iostream>      // for std::string, std::vector
#include <ncurses.h>     // ncurses library
#include <vector>        // std::vector
#include <string>        // std::string
#include <unistd.h>      // usleep for animation delay
#include <locale.h>      // setlocale for UTF-8/emoji support
#include "../game.h"     // declaration of tutorial2()

using namespace std;

// Typewriter-style animated print with horizontal centering
void print_centered_animated(WINDOW *win, int y, const string &text, int delay = 15000) {
    int x = (getmaxx(win) - static_cast<int>(text.length())) / 2;
    for (char c : text) {
        mvwaddch(win, y, x++, c);
        wrefresh(win);
        usleep(delay);
    }
}

int tutorial1(WINDOW *game_win)
{
    setlocale(LC_ALL, "");  // Enable emoji and UTF-8 support

    int HEIGHT, WIDTH;
    getmaxyx(game_win, HEIGHT, WIDTH);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    int ch;

    while (true)
    {
        werase(game_win);
        box(game_win, 0, 0);

        vector<string> lines = {
            "🎮 Buckshot Roulette: Tutorial",
            "",
            "Welcome to Buckshot Roulette.",
            "A psychological shootout between you and the dealer.",
            "Your life depends on a chambered round.",
            "",
            "You’ll take turns with the dealer — spin the cylinder and pull the trigger.",
            "Each round could be a blank... or a live shot.",
            "",
            "🎯 Goal: Survive and outlast the dealer.",
            "Each shootout has 9 rounds. If one of you reaches 0 HP, game over."
        };

        int start_y = (HEIGHT - static_cast<int>(lines.size())) / 2;

        for (size_t i = 0; i < lines.size(); ++i) {
            print_centered_animated(game_win, start_y + i, lines[i]);
        }

        // Instructions at bottom
        string escape = "Press ESC to return";
        mvwprintw(game_win, HEIGHT - 3, (WIDTH - static_cast<int>(escape.size())) / 2, "%s", escape.c_str());

        string arrow = "-->";
        mvwprintw(game_win, HEIGHT - 3, WIDTH - 10, "%s", arrow.c_str());

        wrefresh(game_win);

        // Input
        ch = wgetch(game_win);
        if (ch == KEY_RIGHT) {
            tutorial2(game_win);
            break;
        } else if (ch == 27) {
            return 1;
        }
    }
    return 0;
}
