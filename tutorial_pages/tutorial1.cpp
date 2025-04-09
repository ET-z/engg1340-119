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

    string hello = "Tutorial 1";
    mvwprintw(game_win, HEIGHT / 2, (WIDTH - static_cast<int>(hello.size())) / 2, "%s", hello.c_str());
    string escape = "Press ESC to return";
    mvwprintw(game_win, 10, (WIDTH - static_cast<int>(escape.size())) / 2, "%s", escape.c_str());
    string arrow = "-->";
    mvwprintw(game_win, HEIGHT / 2, (WIDTH - static_cast<int>(arrow.size())) - 10, "%s", arrow.c_str());

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