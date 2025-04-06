#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "game.h"
using namespace std;

int game(WINDOW *game_win)
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

    string hello = "Game Window";
    mvwprintw(game_win, HEIGHT / 2, (WIDTH - static_cast<int>(hello.size())) / 2, "%s", hello.c_str());

    // Display changes
    wrefresh(game_win);

    // User input
    ch = wgetch(game_win);
  }
  // Clean up ncurses
  endwin();

  return 0;
}