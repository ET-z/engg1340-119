#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "game.h"
using namespace std;

void draw_dealer(WINDOW *game_win)
{
  int HEIGHT, WIDTH;
  getmaxyx(game_win, HEIGHT, WIDTH);
  // Color pair (This is white text on a blue background)
  init_pair(1, COLOR_RED, COLOR_BLACK);

  vector<string> dealer = {
      "                mqn                ",
      "         hAAAAAAAAAAAAAAAAq        ",
      "       AAAAAAAURAAAVhhAAAAAAn      ",
      "     AAAh   yGWhhhhD     hhFAA3    ",
      "    DA        ShAA1F        AAAM   ",
      "    AB        hEAAhB        yvlN   ",
      "  hAIm        AAAAAD         AAAAA ",
      " AAAAAAhh    hAAAAAACG    hAAAh AAx",
      " Ar  hAAAAAAAnLAAAAAhuRAAAAh     A ",
      " A      zhAAAAAhh1hhAAAAAv  A1   A ",
      " AA    AA r  xqAAAAAhh  0 ETc   hh ",
      "  ABc9v  vA tAmx     A  A7 RL5 hh  ",
      "   mhA ZNh  B  d8 BF jA  dA  w4h   ",
      "     TAA  e     E  X   A   AAEh    ",
      "       AAAAC           rAAAA       ",
      "          hAAAAAAAAAAAAA3          ",
      "                                   "};

  // Calculate starting position to center the dealer
  int start_y = 12;
  int start_x = (WIDTH / 2 - dealer[0].length()) / 2;

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

  vector<string> player = {
      "              __               ",
      "           .'  `'.             ",
      "          /  _    |            ",
      "          #_/.\\==/.\\           ",
      "         (, \\\\_/ \\\\_/          ",
      "          |    -' |            ",
      "          \\\\   '=  /           ",
      "          /`-.__.'             ",
      "       .-'`-.___|__            ",
      "      /    \\\\       `.         "};

  // Calculate starting position to center the dealer
  int start_y = 15;
  int start_x = (WIDTH - player[0].length()) / 2 + WIDTH / 2 - player[0].length();

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