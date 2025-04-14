#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include "game.h"
using namespace std;

void draw_dealer(WINDOW *game_win)
{
  int HEIGHT, WIDTH;
  getmaxyx(game_win, HEIGHT, WIDTH);
  // Color pair (This is white text on a blue background)
  init_pair(1, COLOR_RED, COLOR_BLACK);

  // Track progress of player
  ifstream fin;
  fin.open("dealer_animation/dealer.txt");

  if (fin.fail())
  {
    exit(1);
  }
  vector<string> dealer;
  string line;
  while (getline(fin, line))
  {
    dealer.push_back(line);
  }
  fin.close();

  // Calculate starting position to center the dealer
  int start_y = 10;
  int start_x = (WIDTH / 2 - dealer[0].length()) / 2 - 10;

  // Set the color pair for the dealer
  wattron(game_win, COLOR_PAIR(1));

  // Draw each row of the dealer
  for (size_t i = 0; i < dealer.size(); i++)
  {
    mvwprintw(game_win, start_y + i, start_x, "%s", dealer[i].c_str());
  }

  // Turn off the color pair
  wattroff(game_win, COLOR_PAIR(1));

  return;
}

void draw_player(WINDOW *game_win)
{
  int HEIGHT, WIDTH;
  getmaxyx(game_win, HEIGHT, WIDTH);
  // Color pair (This is white text on a blue background)
  init_pair(2, COLOR_BLUE, COLOR_BLACK);

  // Track progress of player
  ifstream fin;
  fin.open("player_animation/player.txt");

  if (fin.fail())
  {
    exit(1);
  }
  vector<string> player;
  string line;
  while (getline(fin, line))
  {
    player.push_back(line);
  }
  fin.close();

  // Calculate starting position to center the dealer
  int start_y = 10;
  int start_x = (WIDTH - player[0].length()) / 2 + WIDTH / 2 - player[0].length() + 10;

  // Set the color pair for the dealer
  wattron(game_win, COLOR_PAIR(2));

  // Draw each row of the dealer
  for (size_t i = 0; i < player.size(); i++)
  {
    mvwprintw(game_win, start_y + i, start_x, "%s", player[i].c_str());
  }

  // Turn off the color pair
  wattroff(game_win, COLOR_PAIR(2));

  return;
}