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
  init_pair(1, COLOR_WHITE, COLOR_BLUE);    // Reserved
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);  // Titles
  init_pair(3, COLOR_WHITE, COLOR_BLACK);   // Body text

  int ch;
  while (true)
  {
    werase(game_win);
    box(game_win, 0, 0);

    // 📄 Moves Title (yellow)
    wattron(game_win, A_BOLD | COLOR_PAIR(2));
    print_animated(game_win, 2, "📄 Your Moves:");
    wattroff(game_win, A_BOLD | COLOR_PAIR(2));

    int y = 4;
    vector<string> lines = {
      "- s → Shoot yourself 💥",
      "- o → Shoot the dealer 🎯",
      "- e → Use an item 🧪",
      "- Arrow keys → Navigate inventory ↕️",
      "- ENTER or SPACE → Confirm action ✅",
    };

    wattron(game_win, COLOR_PAIR(3));  // Body in white
    for (const auto &line : lines) {
      print_animated(game_win, y++, line);
    }
    wattroff(game_win, COLOR_PAIR(3));

    // 📦 Items Title (yellow)
    y += 1;
    wattron(game_win, A_BOLD | COLOR_PAIR(2));
    print_animated(game_win, y++, "📦 Items:");
    wattroff(game_win, A_BOLD | COLOR_PAIR(2));

    vector<string> items = {
      "- 🚬 Cigarette → +1 HP",
      "- 🔪 Knife → Double your damage",
      "- 🧴 Beer → Discard and see the next shell",
      "- 🔭 Scope → See if the next shell is live",
      "- ⛓️ Handcuff → Skip the dealer's turn"
    };

    wattron(game_win, COLOR_PAIR(3));  // Body in white
    for (const auto &item : items) {
      print_animated(game_win, y++, item);
    }
    wattroff(game_win, COLOR_PAIR(3));

    // Navigation prompt
    y += 2;
    wattron(game_win, A_BOLD | COLOR_PAIR(3));
    print_animated(game_win, y++, "⬅️ Back  |  ➡️ Continue  |  ESC to exit");
    wattroff(game_win, A_BOLD | COLOR_PAIR(3));

    wrefresh(game_win);
    ch = wgetch(game_win);

    if (ch == KEY_RIGHT) {
      tutorial3(game_win);
      break;
    } else if (ch == KEY_LEFT) {
      tutorial1(game_win);
      break;
    } else if (ch == 27) {
      return 1;
    }
  }
  return 0;
}
