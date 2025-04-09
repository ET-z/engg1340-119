#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "game.h"
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

    string hello = "Tutorial 2";
    mvwprintw(game_win, HEIGHT / 2, (WIDTH - static_cast<int>(hello.size())) / 2, "%s", hello.c_str());
    string escape = "Press ESC to return";
    mvwprintw(game_win, 10, (WIDTH - static_cast<int>(escape.size())) / 2, "%s", escape.c_str());
    vector<string> arrows = {"<--", "-->"};
    mvwprintw(game_win, HEIGHT / 2, 10, "%s", arrows[0].c_str());
    mvwprintw(game_win, HEIGHT / 2, (WIDTH - static_cast<int>(arrows[1].size())) - 10, "%s", arrows[1].c_str());

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
  // Clean up ncurses
  endwin();

  return 0;
}