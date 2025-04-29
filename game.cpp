#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "game.h"
#include "shell.h"
#include "draw_healthbar.h"
#include "player.h"
#include "dealerAI.h"
extern DealerAILevel currentDealerAILevel;
using namespace std;
int currentRound = 0;
vector<bool> rounds;

// Declare healthbar
void healthbar(WINDOW *bar, int health);

int game(WINDOW *game_win)
{
  int HEIGHT, WIDTH;
  getmaxyx(game_win, HEIGHT, WIDTH);

  // Color pair
  init_pair(1, COLOR_WHITE, COLOR_BLUE);

  int ch;

  // Height + width for inventory item boxes
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
  int health_height = 3, health_width = 72;

  // Dealer health bar
  int dealer_health_start_y = 1;
  int dealer_health_start_x = 2;
  WINDOW *dealer_health = derwin(game_win, health_height, health_width, dealer_health_start_y, dealer_health_start_x);

  // Player health bar
  int player_health_start_y = 1;
  int player_health_start_x = WIDTH - health_width - 2;
  WINDOW *player_health = derwin(game_win, health_height, health_width, player_health_start_y, player_health_start_x);

  // Window dimensions
  int draw_height = 19, draw_width = 60;

  // Dealer draw window
  int dealer_draw_start_y = 10;
  int dealer_draw_start_x = 1;
  WINDOW *dealer_draw = derwin(game_win, draw_height, draw_width, dealer_draw_start_y, dealer_draw_start_x);

  // Player draw window
  int player_draw_start_y = 10;
  int player_draw_start_x = WIDTH - draw_width - 1;
  WINDOW *player_draw = derwin(game_win, draw_height, draw_width, player_draw_start_y, player_draw_start_x);

  // Bullet table
  int bullet_table_height = 20, bullet_table_width = 30;
  int bullets_start_y = HEIGHT - bullet_table_height - 1;
  int bullets_start_x = (WIDTH - bullet_table_width) / 2;
  WINDOW *bullets_table = derwin(game_win, bullet_table_height, bullet_table_width, bullets_start_y, bullets_start_x);

  // Game state variables and initiate players, shells
  int selectedRow = 0, selectedCol = 0;
  bool itemPicked = false;
  Player player("ENGG1340", 60, true);
  Opponent AI("S1mple", 60, false);
  int playerHealth = player.health;
  int dealerHealth = AI.health;
  ShellGenerator gen;
  string a = gen.getShells();

  healthbar(player_health, playerHealth);
  healthbar(dealer_health, dealerHealth);

  // Main loop
  while (true)
  {
    // Clear game window
    wclear(game_win);
    // Redraw boxes
    box(game_win, 0, 0);
    healthbar(player_health, playerHealth);
    healthbar(dealer_health, dealerHealth);
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

    // Highlight player inventory selection
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 4; j++)
      {
        if (i == selectedRow && j == selectedCol)
          wattron(player_items[i][j], A_REVERSE);
        box(player_items[i][j], 0, 0);
        if (i == selectedRow && j == selectedCol)
          wattroff(player_items[i][j], A_REVERSE);
        wrefresh(player_items[i][j]);
      }

    string pause_msg = "Press ESC to pause";

    mvwprintw(game_win, 1, (WIDTH - static_cast<int>(pause_msg.size())) / 2, "%s", pause_msg.c_str());

    // Display changes
    wrefresh(game_win);

    // draw dealer and player
    draw_player(player_draw);
    draw_dealer(dealer_draw);

    wrefresh(game_win);

    // User input
    ch = wgetch(game_win);

    // Handle input
    switch (ch)
    {
    case 27: // ESC
    {
      int result = ::pause();
      if (result == 0)
        continue;
      else if (result == 1)
        return 1;
      else if (result == 2)
      {
        for (auto &row : dealer_items)
          for (WINDOW *win : row)
            delwin(win);

        for (auto &row : player_items)
          for (WINDOW *win : row)
            delwin(win);

        delwin(dealer_health);
        delwin(player_health);
        delwin(bullets_table);
        delwin(dealer_draw);
        delwin(player_draw);
        delwin(game_win);
        endwin();
        return 0;
      }
      break;
    }

    case KEY_UP:
      if (selectedRow > 0)
        selectedRow--;
      break;

    case KEY_DOWN:
      if (selectedRow < 1)
        selectedRow++;
      break;

    case KEY_LEFT:
      if (selectedCol > 0)
        selectedCol--;
      break;

    case KEY_RIGHT:
      if (selectedCol < 3)
        selectedCol++;
      break;

    case 'e':
    case 'E':
      itemPicked = true;
      // highlight selected box
      mvwprintw(player_items[selectedRow][selectedCol], 1, 1, "Picked");
      break;

    case 10:  // Enter key
    case ' ': // Spacebar
      if (itemPicked)
      {
        playerHealth = min(playerHealth + 1, 100); // DEMO: if user pick cig (heals + 1)
        itemPicked = false;
      }
      else
      {

        static vector<bool> rounds;    // current shell
        static int currentRound = 0;   // cirrent bullet
        static bool playerTurn = true; // playerturn signal

        if (rounds.empty() || currentRound >= rounds.size())
        {
          ShellGenerator gen;
          string shellStr = gen.getShells();
          rounds.clear();
          for (char c: shellStr){
            rounds.push_back(c == '1');
          }
          currentRound = 0;
        }

        // DRAW UI：hint player to choose
        mvwprintw(game_win, 5, 2, "Choose your action: [1] Shoot Dealer  [2] Shoot Yourself");
        wrefresh(game_win);

        // player option selection
        int action = wgetch(game_win);

        if (playerTurn)
        {
          if (action == '1')
          { // Shoot Dealer
            bool result = rounds[currentRound++];
            if (result)
            { // live shell
              dealerHealth = max(dealerHealth - 20, 0);
              mvwprintw(game_win, 6, 2, "A live shell! Dealer takes 20 damage.");
              playerTurn = false;
            }
            else
            { // blank shell
              mvwprintw(game_win, 6, 2, "Oops! Blank! Your turn ends.");
              playerTurn = false;
            }
          }
          else if (action == '2')
          { // Shoot Self
            bool result = rounds[currentRound++];
            if (result)
            { // live shell
              playerHealth = max(playerHealth - 20, 0);
              mvwprintw(game_win, 6, 2, "You shot yourself with a live shell! -20 HP.");
              playerTurn = false;
            }
            else
            { // blank shell
              mvwprintw(game_win, 6, 2, "Blank! Lucky! Shoot again.");
              playerTurn = true; // Blank self-shot => keep turn
            }
          }
          else
          {
            mvwprintw(game_win, 6, 2, "Invalid choice. Turn skipped.");
            playerTurn = false;
          }
        }

        // CHECK if player or dealer dead after player turn
        if (playerHealth <= 0)
        {
          mvwprintw(game_win, 8, 2, "You died! Dealer wins!");
          wrefresh(game_win);
          getch();
          return 0;
        }
        if (dealerHealth <= 0)
        {
          mvwprintw(game_win, 8, 2, "Dealer died! You win!");
          wrefresh(game_win);
          getch();
          return 0;
        }

        // If it's Dealer's turn now
        if (!playerTurn)
        {
          int remainingLiveShells = count(rounds.begin() + currentRound, rounds.end(), true);
          int remainingTotalShells = rounds.size() - currentRound;

          dealerAI(game_win, playerHealth, dealerHealth, rounds[currentRound++], remainingLiveShells, remainingTotalShells, currentDealerAILevel);

          playerTurn = true;
        }

        // Dealer action blood check
        if (playerHealth <= 0)
        {
          mvwprintw(game_win, 8, 2, "You died! Dealer wins!");
          wrefresh(game_win);
          getch();
          return 0;
        }
      }

      // If shells are finished after AI or player
      if (currentRound >= rounds.size())
      {
        ShellGenerator gen;
        string shellString = gen.getShells();
        rounds.clear();
        for (char c : shellString){
          rounds.push_back(c == '1');
        }
        currentRound = 0;
        mvwprintw(game_win, 9, 2, "Reloading a new clip...");
        wrefresh(game_win);
      }
    }

    break;
  }
  // Clean up ncurses
  delwin(game_win);
  endwin();

  return 0;
}
