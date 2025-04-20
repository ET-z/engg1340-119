#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <locale.h>
#include <unistd.h>
#include "../game.h"
using namespace std;

void print_animated(WINDOW *win, int y, const string &text, int delay = 20000) {
  int x = (getmaxx(win) - text.length()) / 2;
  for (size_t i = 0; i < text.length(); ++i) {
    mvwaddch(win, y, x + i, text[i]);
    wrefresh(win);
    usleep(delay);
  }
}

int tutorial2(WINDOW *game_win)
{
  int HEIGHT, WIDTH;
  getmaxyx(game_win, HEIGHT, WIDTH);
  init_pair(1, COLOR_WHITE, COLOR_BLUE);

  int ch;
  while (true)
  {
    werase(game_win);
    box(game_win, 0, 0);

    wattron(game_win, A_BOLD);
    print_animated(game_win, 2, "📄 Your Moves:");
    wattroff(game_win, A_BOLD);

    int y = 4;
    vector<string> lines = {
      "- s → Shoot yourself 💥",
      "- o → Shoot the dealer 🎯",
      "- e → Use an item 🧪",
      "- Arrow keys → Navigate inventory ↕️",
      "- ENTER or SPACE → Confirm action ✅",
    };
    for (const auto &line : lines) {
      print_animated(game_win, y++, line);
    }

    y += 1;
    wattron(game_win, A_BOLD);
    print_animated(game_win, y++, "📦 Items:");
    wattroff(game_win, A_BOLD);

    vector<string> items = {
      "- 🚬 Cigarette → +1 HP",
      "- 🔪 Knife → Double your damage",
      "- 🧴 Beer → Discard and see the next shell",
      "- 🔭 Scope → See if the next shell is live",
      "- ⛓️ Handcuff → Skip the dealer's turn"
    };
    for (const auto &item : items) {
      print_animated(game_win, y++, item);
    }

    y += 2;
    print_animated(game_win, y++, "⬅️ Back  |  ➡️ Continue  |  ESC to exit");

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
