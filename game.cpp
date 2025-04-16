#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "game.h"
#include "player.h"

using namespace std;

void inirand() {srand(time(NULL));}
int randomsh()
{
	int shell = rand() % 2;
	return shell;
}

int game(WINDOW *game_win)
{
  int HEIGHT, WIDTH;
  getmaxyx(game_win, HEIGHT, WIDTH);

  // Color pair (This is white text on a blue background)
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  int ch;
  string disp = "";
  const int rnum = 9;
  inirand();
  int rounds[rnum];
  for (int i = 0; i < rnum; i++)
    {	
    	rounds[i] = randomsh();
	disp += to_string(rounds[i]) + "   ";
    }
  wclear(game_win);
  mvwprintw(game_win, HEIGHT / 2 + 1,  2, "%s", disp.c_str());
	
  Player player("Test", 60, true);
  Opponent AI("Aggressive", 60, false);

  box(game_win, 0, 0);
  // Menu loop
  for (int i = 0; i < rnum; i++){
	mvwprintw(game_win, HEIGHT / 2 + 3, 2, "%s", to_string(i).c_str());
	if (player.isTurn){
		int ch = wgetch(game_win);
		mvwprintw(game_win, HEIGHT / 2 + 4, 2, "%s", to_string(static_cast<char>(ch)).c_str());
		if (ch == 's'){
			if(rounds[i]){
				player.takeDamage(20);
				player.endTurn();
				AI.begTurn();
			}
		} else {
			if(rounds[i]){
				AI.takeDamage(20);
				player.endTurn();
				AI.begTurn();
			} else {
				player.endTurn();
			      	AI.begTurn();	
			}
		}
	} else if (AI.isTurn){
		if(rounds[i]){
			player.takeDamage(20);
			AI.endTurn();
			player.begTurn();
		} else {
			 AI.endTurn();
			 player.begTurn();
		}
	
	}
	mvwprintw(game_win, HEIGHT / 2 + 5, 2, "%s", to_string(player.health).c_str());
	mvwprintw(game_win, HEIGHT / 2 + 6, 2, "%s", to_string(AI.health).c_str());
	mvwprintw(game_win, HEIGHT / 2 + 7, 2, "%s", to_string(player.isTurn).c_str());
	mvwprintw(game_win, HEIGHT / 2 + 8, 2, "%s", to_string(AI.isTurn).c_str());
	
	

    // Display changes
    wrefresh(game_win);

    // User input
    
  }
  // Clean up ncurses
  endwin();

  return 0;
}
