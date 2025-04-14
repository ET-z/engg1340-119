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

  // Height and width for inventory item boxes
  int inventory_height = 10, inventory_width = 20;

  // Dealer's inventory
  vector<vector<WINDOW *>> dealer_items(2, vector<WINDOW *>(4));
  int dealer_start_y = HEIGHT - 2 * HEIGHT / 5 - 1;
  int dealer_start_x = 1;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dealer_items[i][j] = derwin(game_win, inventory_height, inventory_width,
                                  dealer_start_y + i * inventory_height,
                                  dealer_start_x + j * inventory_width);
    }
  }

  // Player's inventory
  vector<vector<WINDOW *>> player_items(2, vector<WINDOW *>(4));
  int player_start_y = HEIGHT - 2 * HEIGHT / 5 - 1;
  int player_start_x = WIDTH - 4 * inventory_width - 1;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      player_items[i][j] = derwin(game_win, inventory_height, inventory_width,
                                  player_start_y + i * inventory_height,
                                  player_start_x + j * inventory_width);
    }
  }

  // Height and width for health bars
  int health_height = 9, health_width = 80;

  // Dealer health bar
  int dealer_health_start_y = 1;
  int dealer_health_start_x = 1;
  WINDOW *dealer_health = derwin(game_win, health_height, health_width, dealer_health_start_y, dealer_health_start_x);

  // Player health bar
  int player_health_start_y = 1;
  int player_health_start_x = WIDTH - health_width - 1;
  WINDOW *player_health = derwin(game_win, health_height, health_width, player_health_start_y, player_health_start_x);

  // Bullet Table
  int bullet_table_height = 20, bullet_table_width = 30;
  int bullets_start_y = HEIGHT - bullet_table_height - 1;
  int bullets_start_x = (WIDTH - bullet_table_width) / 2;
  WINDOW *bullets_table = derwin(game_win, bullet_table_height, bullet_table_width, bullets_start_y, bullets_start_x);

  // Main loop
  while (true)
  {
    // Clear game window
    wclear(game_win);
    // Redraw boxes
    box(game_win, 0, 0);
    box(dealer_health, 0, 0);
    wrefresh(dealer_health);
    box(player_health, 0, 0);
    wrefresh(player_health);
    box(bullets_table, 0, 0);
    wrefresh(bullets_table);

    for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        box(dealer_items[i][j], 0, 0);
        wrefresh(dealer_items[i][j]);
      }
    }

    for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        box(player_items[i][j], 0, 0);
        wrefresh(player_items[i][j]);
      }
    }

    string pause = "Press ESC to pause";

    mvwprintw(game_win, 1, (WIDTH - static_cast<int>(pause.size())) / 2, "%s", pause.c_str());

    // draw dealer and player
    draw_dealer(game_win);
    draw_player(game_win);

    // Display changes
    wrefresh(game_win);

    // User input
    ch = wgetch(game_win);

    if (ch == 27) // ESC key - PAUSE game
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
          break;
        }
        else if (p_ch == 'm') // Back to main menu
        {
          delwin(pause_win);
          return 1; // Return 1 to indicate returning to main menu
        }
        else if (p_ch == 'q') // Quit
        {
          delwin(pause_win);
          delwin(game_win);
          for (auto &row : dealer_items)
          {
            for (WINDOW *win : row)
            {
              delwin(win);
            }
          }

          for (auto &row : player_items)
          {
            for (WINDOW *win : row)
            {
              delwin(win);
            }
          }

          delwin(dealer_health);
          delwin(player_health);
          delwin(bullets_table);
          endwin();
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
            break;
          }
          else if (current_selection == 1) // 1 = Return to menu
          {
            delwin(pause_win);
            return 1; // Return 1 to indicate returning to main menu
          }
          else if (current_selection == 2) // 2 - Quit
          {
            for (auto &row : dealer_items)
            {
              for (WINDOW *win : row)
              {
                delwin(win);
              }
            }

            for (auto &row : player_items)
            {
              for (WINDOW *win : row)
              {
                delwin(win);
              }
            }

            delwin(dealer_health);
            delwin(player_health);
            delwin(bullets_table);
            delwin(pause_win);
            delwin(game_win);
            endwin();
          }
        }
      }
    }
  }
  // Clean up ncurses
  delwin(game_win);
  endwin();

  return 0;
}