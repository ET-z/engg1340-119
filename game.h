#ifndef GAME_H
#define GAME_H

int main();
int game(WINDOW *game_win);
int tutorial1(WINDOW *game_win);
int tutorial2(WINDOW *game_win);
int tutorial3(WINDOW *game_win);
int pause();

void draw_dealer(WINDOW *dealer_draw);
void draw_player(WINDOW *player_draw);
void draw_dealer_single(WINDOW *player_draw);
void healthbar(WINDOW *bar, int health);
#endif
