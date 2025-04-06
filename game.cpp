#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "game.h"
using namespace std;

int game(int HEIGHT, int WIDTH)
{
  // Initialize ncurses
  initscr();
  keypad(stdscr, TRUE); // Enable keypad input
  noecho();             // Don't echo keypresses
  curs_set(0);          // Hide the cursor
  // Enable color support if available
  if (has_colors())
  {
    start_color();
  }

  int start_y = (LINES - HEIGHT) / 2;
  int start_x = (COLS - WIDTH) / 2;
  WINDOW *game_win = newwin(HEIGHT, WIDTH, start_y, start_x);
  keypad(game_win, TRUE);
  box(game_win, 0, 0);

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
    mvprintw(LINES / 2, (COLS - static_cast<int>(hello.size())) / 2, "%s", hello.c_str());

    // Display changes
    wrefresh(game_win);

    // User input
    ch = getch();
  }
  // Clean up ncurses
  endwin();

  return 0;
}