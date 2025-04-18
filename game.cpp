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

  // Draw window dimensions
  int draw_height = 19, draw_width = 60;

  // Dealer Draw Window
  int dealer_draw_start_y = 10;
  int dealer_draw_start_x = 1;
  WINDOW *dealer_draw = derwin(game_win, draw_height, draw_width, dealer_draw_start_y, dealer_draw_start_x);

  // Player Draw Window
  int player_draw_start_y = 10;
  int player_draw_start_x = WIDTH - draw_width - 1;
  WINDOW *player_draw = derwin(game_win, draw_height, draw_width, player_draw_start_y, player_draw_start_x);

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
    // box(dealer_draw, 0, 0);
    // wrefresh(dealer_draw);
    // box(player_draw, 0, 0);
    // wrefresh(player_draw);

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

    string pause_msg = "Press ESC to pause";

    mvwprintw(game_win, 1, (WIDTH - static_cast<int>(pause_msg.size())) / 2, "%s", pause_msg.c_str());

    // Display changes
    wrefresh(game_win);

    // draw dealer and player
    draw_dealer(dealer_draw);
    draw_player(player_draw);

    wrefresh(game_win);

    // User input
    ch = wgetch(game_win);

    if (ch == 27) // ESC key - PAUSE game
    {
      int result = ::pause();
      if (result == 0)
      {
        continue;
      }
      else if (result == 1)
      {
        return 1; // return to main menu
      }
      else if (result == 2)
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
        delwin(dealer_draw);
        delwin(player_draw);
        delwin(game_win);
        endwin();
      }
    }
  }
  // Clean up ncurses
  delwin(game_win);
  endwin();

  return 0;
}