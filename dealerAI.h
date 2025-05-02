#ifndef DEALERAI_H
#define DEALERAI_H

#include <ncurses.h>

enum DealerAILevel
{
    DUMB,
    SCOPE_AWARE,
    RISK_AWARE,
    SMART
};

void dealerDumb(WINDOW *game_win, int &playerHealth, bool currentShell);
void dealerScopeAware(WINDOW *game_win, int &playerHealth, bool currentShell);
void dealerRiskAware(WINDOW *game_win, int &playerHealth, int &dealerHealth, int liveCount, int totalShells, bool currentShell, bool &playerTurn);
void dealerSmart(WINDOW *game_win, int &playerHealth, int &dealerHealth, bool currentShell, int liveCount, int totalShells, bool &playerTurn);
void dealerAI(WINDOW *game_win, int &playerHealth, int &dealerHealth, bool currentShell, int liveCount, int totalShells, DealerAILevel aiLevel, bool &playerTurn);

#endif
