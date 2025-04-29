#ifndef DEALER_AI_H
#define DEALER_AI_H

#include <ncurses.h>

enum DealerAILevel {
    DUMB,
    SCOPE_AWARE,
    RISK_AWARE,
    SMART
};


void dealerAI(WINDOW *game_win, int &playerHealth, int &dealerHealth, bool currentShell, int liveCount, int totalShells, DealerAILevel aiLevel);

#endif
