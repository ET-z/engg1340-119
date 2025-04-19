#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "../game.h"
using namespace std;

int tutorial1(WINDOW *game_win)
{
  int HEIGHT, WIDTH;
  getmaxyx(game_win, HEIGHT, WIDTH);

  // Color pair (This is white text on a blue background)
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  int ch;

  // Menu loop
  while (true)
  {
    // Clear game window
    wclear(game_win);
    // Redraw box
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
      "Each shootout has 9 rounds. If one of you reaches 0 HP, game over.",
    };

for (size_t i = 0; i < lines.size(); ++i) {
  mvwprintw(game_win, 2 + i, 4, "%s", lines[i].c_str());
}


    // Display changes
    wrefresh(game_win);

    // User input
    ch = wgetch(game_win);

    if (ch == KEY_RIGHT) // Start
    {
      tutorial2(game_win);
      break;
    }
    else if (ch == 27) // How to play
    {
      return 1;
    }
  }
  return 0;
}
