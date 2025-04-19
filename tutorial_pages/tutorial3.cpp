#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "../game.h"
using namespace std;

int tutorial3(WINDOW *game_win)
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
      "🧠 About the Dealer (AI):",
      "",
      "- The dealer will always shoot at you on their turn.",
      "- You can disrupt their turn using items like Handcuffs.",
      "",
      "❤️ Health Info:",
      "- You and the dealer start at 60 HP.",
      "- A live round deals 20 damage.",
      "- Reduce the dealer’s HP to 0 to win.",
      "",
      "⏸ Pause & Exit:",
      "- ESC → Pause the game",
      "- M → Return to Main Menu",
      "- Q → Quit",
      "",
      "Good luck. Outplay the dealer."
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
      // tutorial4(game_win);
    }
    else if (ch == KEY_LEFT) // How to play
    {
      tutorial2(game_win);
      break;
    }
    else if (ch == 27) // Return to main menu
    {
      return 1;
    }
  }
  return 0;
}
