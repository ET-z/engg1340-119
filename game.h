#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <vector>
#include <string>
using namespace std;

struct GameWindows {
    //a struct to store all window pointers
    vector<vector<WINDOW *>> dealer_items;
    vector<vector<string>> dealer_item_texts;
    vector<vector<WINDOW *>> player_items;
	vector<vector<string>> player_item_texts;
    
    WINDOW * dealer_health;
    WINDOW * player_health;

    WINDOW * dealer_draw;
    WINDOW * player_draw;

    WINDOW * bullets_table;

    //constructor
    GameWindows() : player_items(2, std::vector<WINDOW*>(4, nullptr)),
                    dealer_items(2, std::vector<WINDOW*>(4, nullptr)),
                    player_item_texts(2, vector<string>(4, "")),
                    dealer_item_texts(2, vector<string>(4, "")),
                    player_health(nullptr), dealer_health(nullptr),
                    player_draw(nullptr), dealer_draw(nullptr),
                    bullets_table(nullptr)
    {}
};

GameWindows initGameWindows (WINDOW * game_win);
void delGameWindows (GameWindows& windows);

int main();
int game(WINDOW *game_win);
int tutorial1(WINDOW *game_win);
int tutorial2(WINDOW *game_win);
int tutorial3(WINDOW *game_win);
int pause();

void draw_dealer(WINDOW *dealer_draw);
void draw_player(WINDOW *player_draw);
void draw_dealer_single(WINDOW *dealer_draw);
void healthbar(WINDOW *bar, int health);
#endif
