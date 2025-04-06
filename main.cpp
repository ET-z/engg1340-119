#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "game.h"
using namespace std;

int main()
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

  // Window dimensions
  int HEIGHT = 50, WIDTH = 100;

  // Check if the game window is big enough
  while (LINES < HEIGHT || COLS < WIDTH)
  {
    clear();
    string one = "Screen not big enough";
    string two = "Zoom out and increase window size!";
    string three = "Press any key to re-check";
    mvprintw(LINES / 2, (COLS - static_cast<int>(one.size())) / 2, "%s", one.c_str());
    mvprintw(LINES / 2 + 1, (COLS - static_cast<int>(two.size())) / 2, "%s", two.c_str());
    mvprintw(LINES / 2 + 2, (COLS - static_cast<int>(three.size())) / 2, "%s", three.c_str());
    refresh();
    getch();
  }
  int start_y = (LINES - HEIGHT) / 2;
  int start_x = (COLS - WIDTH) / 2;
  WINDOW *game_win = newwin(HEIGHT, WIDTH, start_y, start_x);
  keypad(game_win, TRUE);
  box(game_win, 0, 0);

  // Menu items
  const vector<string> menu_items = {"Star Game", "How to Play", "Quit"};
  int menu_size = menu_items.size();
  int current_selection = 0;
  int ch;

  // Color pair (This is white text on a blue background)
  init_pair(1, COLOR_WHITE, COLOR_BLUE);

  // Menu loop
  while (true)
  {
    // Clear game window
    wclear(game_win);
    // Redraw box
    box(game_win, 0, 0);

    // Center menu items vertically
    int start_row = (HEIGHT - menu_size) / 2;

    for (int i = 0; i < menu_size; ++i)
    {
      // Center menu items horizontally
      int start_col = (WIDTH - menu_items[i].length()) / 2; // Center each item horizontally
      if (i == current_selection)
      {
        wattron(game_win, A_REVERSE);
      }

      mvwprintw(game_win, start_row + i, start_col, "%s", menu_items[i].c_str());

      if (i == current_selection)
      {
        wattroff(game_win, A_REVERSE);
      }
    }

    // Display changes
    wrefresh(game_win);

    // User input
    ch = wgetch(game_win);

    // User input to pick menu item
    if (ch == KEY_UP)
    {
      current_selection = (current_selection - 1 + menu_size) % menu_size;
    }
    else if (ch == KEY_DOWN)
    {
      current_selection = (current_selection + 1) % menu_size;
    }
    else if (ch == KEY_ENTER || ch == '\n')
    {
      // Check user selection: 0 = Start game, 1 = How to Play, 2 = Quit
      if (current_selection == 0)
      {
        game(HEIGHT, WIDTH);
        delwin(game_win);
        break;
      }
      else if (current_selection == 1)
      {
        tutorial(HEIGHT, WIDTH);
        delwin(game_win);
        break;
      }
      else if (current_selection == 2)
      {
        break;
      }
    }
  }
  // Clean up ncurses
  endwin();

  return 0;
}