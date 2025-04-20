#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <locale.h>
#include <unistd.h>
#include "../game.h"
using namespace std;

// Animation helper
void print_animated(WINDOW *win, int y, const string &text, int delay = 20000) {
  int x = (getmaxx(win) - static_cast<int>(text.length())) / 2;
  wattron(win, COLOR_PAIR(3));
  for (size_t i = 0; i < text.length(); ++i) {
    mvwaddch(win, y, x + i, text[i]);
    wrefresh(win);
    usleep(delay);
  }
  wattroff(win, COLOR_PAIR(3));
}

int tutorial3(WINDOW *game_win)
{
  int HEIGHT, WIDTH;
  getmaxyx(game_win, HEIGHT, WIDTH);
  start_color();

  // Color pairs
  init_pair(1, COLOR_WHITE, COLOR_BLUE);    // Optional use
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);  // Section titles
  init_pair(3, COLOR_BLUE, COLOR_BLACK);    // Main body

  int ch;
  while (true)
  {
    werase(game_win);
    box(game_win, 0, 0);

    vector<string> lines = {
      "🧠 About the Dealer (AI):",
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

    int y = 2;
    for (size_t i = 0; i < lines.size(); ++i) {
      if (lines[i].empty()) {
        ++y;
        continue;
      }

      if (lines[i].find("🧠") != string::npos || 
          lines[i].find("❤️") != string::npos || 
          lines[i].find("⏸") != string::npos || 
          lines[i] == "Good luck. Outplay the dealer.") 
      {
        wattron(game_win, A_BOLD | COLOR_PAIR(2)); // Yellow bold
        print_animated(game_win, y++, lines[i]);
        wattroff(game_win, A_BOLD | COLOR_PAIR(2));
      } else {
        wattron(game_win, COLOR_PAIR(3)); // Blue body
        print_animated(game_win, y++, lines[i]);
        wattroff(game_win, COLOR_PAIR(3));
      }
    }

    y += 1;
    wattron(game_win, A_BOLD | COLOR_PAIR(2));
    print_animated(game_win, y++, "⬅️ Back  |  ESC to exit");
    wattroff(game_win, A_BOLD | COLOR_PAIR(2));

    wrefresh(game_win);

    ch = wgetch(game_win);

    if (ch == KEY_LEFT) {
      tutorial2(game_win);
      break;
    } else if (ch == 27) {
      return 1;
    }
  }

  return 0;
}
