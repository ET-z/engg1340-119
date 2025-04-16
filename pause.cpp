#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "game.h"
using namespace std;

int pause()
{
  // Create new pause window
  int height = 25, width = 100;
  int start_y = (LINES - height) / 2;
  int start_x = (COLS - width) / 2;
  WINDOW *pause_win = newwin(height, width, start_y, start_x);
  keypad(pause_win, TRUE);
  box(pause_win, 0, 0);

  const vector<string> menu_items = {"Resume Game | ESC", "Return to menu | m", "Quit | q"};
  int menu_size = menu_items.size();
  int current_selection = 0;

  while (true)
  {
    // Clear pause window
    wclear(pause_win);
    // Redraw box
    box(pause_win, 0, 0);

    // Center pause menu items vertically
    int start_row = (height - menu_size) / 2;

    for (int i = 0; i < menu_size; ++i)
    {
      // Center pause menu items horizontally
      int start_col = (width - menu_items[i].length()) / 2; // Center each item horizontally
      if (i == current_selection)
      {
        wattron(pause_win, A_REVERSE);
      }

      mvwprintw(pause_win, start_row + i, start_col, "%s", menu_items[i].c_str());

      if (i == current_selection)
      {
        wattroff(pause_win, A_REVERSE);
      }
    }

    // Display changes
    wrefresh(pause_win);

    // Pause window user input
    int p_ch = wgetch(pause_win);

    if (p_ch == 27) // Back to game
    {
      delwin(pause_win);
      return 0;
    }
    else if (p_ch == 'm') // Back to main menu
    {
      delwin(pause_win);
      return 1; // Return 1 to indicate returning to main menu
    }
    else if (p_ch == 'q') // Quit
    {
      delwin(pause_win);
      return 2;
    }
    else if (p_ch == KEY_UP)
    {
      current_selection = (current_selection - 1 + menu_size) % menu_size;
    }
    else if (p_ch == KEY_DOWN)
    {
      current_selection = (current_selection + 1) % menu_size;
    }
    else if (p_ch == KEY_ENTER || p_ch == '\n')
    {
      // Check user selection:
      if (current_selection == 0) // 0 = Resume Game
      {
        delwin(pause_win);
        return 0;
      }
      else if (current_selection == 1) // 1 = Return to menu
      {
        delwin(pause_win);
        return 1; // Return 1 to indicate returning to main menu
      }
      else if (current_selection == 2) // 2 - Quit
      {
        delwin(pause_win);
        return 2;
      }
    }
  }

  // Clean up ncurses
  delwin(pause_win);
  endwin();
  return 0;
}