#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include "game.h"
#include "draw_healthbar.h"
using namespace std;

void draw_dealer_single(WINDOW *dealer_draw)
{
  int HEIGHT, WIDTH;
  getmaxyx(dealer_draw, HEIGHT, WIDTH);
  // Color pair (This is white text on a blue background)
  init_pair(1, COLOR_RED, COLOR_BLACK);

  // Track progress of player
  ifstream fin;
  string file = "dealer_animation/0.txt";
  fin.open(file);

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
  int start_y = 0;
  int start_x = (WIDTH - dealer[0].length()) / 2 + 5;

  // Set the color pair for the dealer
  wattron(dealer_draw, COLOR_PAIR(1));

  // Draw each row of the dealer
  for (size_t i = 0; i < dealer.size(); i++)
  {
    mvwprintw(dealer_draw, start_y + i, start_x, "%s", dealer[i].c_str());
  }

  wrefresh(dealer_draw);

  // Turn off the color pair
  wattroff(dealer_draw, COLOR_PAIR(1));

  return;
}

void draw_dealer(WINDOW *dealer_draw)
{
  int HEIGHT, WIDTH;
  getmaxyx(dealer_draw, HEIGHT, WIDTH);
  // Color pair (This is white text on a blue background)
  init_pair(1, COLOR_RED, COLOR_BLACK);

  // Track progress of player
  ifstream fin;
  for (int i = 9; i > -1; i--)
  {
    // box(dealer_draw, 0, 0);

    string file = "dealer_animation/" + to_string(i) + ".txt";
    fin.open(file);

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
    int start_y = 0;
    int start_x = (WIDTH - dealer[0].length()) / 2 + 5;

    // Set the color pair for the dealer
    wattron(dealer_draw, COLOR_PAIR(1));

    // Draw each row of the dealer
    for (size_t i = 0; i < dealer.size(); i++)
    {
      mvwprintw(dealer_draw, start_y + i, start_x, "%s", dealer[i].c_str());
    }

    wrefresh(dealer_draw);

    napms(100); // Pause to show the animation frame
    if (i != 0)
      werase(dealer_draw); // Clear the screen for the next frame
  }

  // Turn off the color pair
  wattroff(dealer_draw, COLOR_PAIR(1));

  return;
}

void draw_player(WINDOW *player_draw)
{
  int HEIGHT, WIDTH;
  getmaxyx(player_draw, HEIGHT, WIDTH);
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
  int start_y = 0;
  int start_x = (WIDTH - player[0].length()) / 2 - 5;

  // Set the color pair for the dealer
  wattron(player_draw, COLOR_PAIR(2));

  // Draw each row of the dealer
  for (size_t i = 0; i < player.size(); i++)
  {
    mvwprintw(player_draw, start_y + i, start_x, "%s", player[i].c_str());
  }

  wrefresh(player_draw);
  // Turn off the color pair
  wattroff(player_draw, COLOR_PAIR(2));

  return;
}
