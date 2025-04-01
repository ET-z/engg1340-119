#include <iostream>
#include <ncurses.h>
using namespace std;

int main()
{
  // Initialize ncurses
  initscr();

  // Enable keypad input
  keypad(stdscr, TRUE);

  // Don't echo keypresses
  noecho();

  // Hide the cursor
  curs_set(0);

  // Enable color support if available
  if (has_colors())
  {
    start_color();
  }

  // Game logic

  // Clean up ncurses
  endwin();

  return 0;
}