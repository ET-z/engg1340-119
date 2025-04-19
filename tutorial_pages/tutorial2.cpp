#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "../game.h"
using namespace std;

int tutorial2(WINDOW *game_win)
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
      "📄 Your Moves:",
      "",
      "- s → Shoot yourself", //not sure
      "- o → Shoot the dealer", // not sure
      "- e → Use an item",
      "- Arrow keys → Navigate inventory",
      "- ENTER or SPACE → Confirm action", //not sure
      "",
      "📦 Items:",
      "- 🚬 Cigarette → +1 HP",
      "- 🔪 Knife → Double your damage",
      "- 🧴 Beer → Discard and see the next shell",
      "- 🔭 Scope → See if the next shell is live",
      "- ⛓️ Handcuff → Skip the dealer's turn",
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
      tutorial3(game_win);
      break;
    }
    else if (ch == KEY_LEFT) // How to play
    {
      tutorial1(game_win);
      break;
    }
    else if (ch == 27) // How to play
    {
      return 1;
    }
  }
  return 0;
}
