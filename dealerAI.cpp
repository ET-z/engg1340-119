#include "dealerAI.h"
#include <cstdlib>
#include <string>
#include <algorithm>

// Dumb AI: Always attack
void dealerDumb(WINDOW *game_win, int &playerHealth) {
    if (rand() % 2 == 1) {
        mvwprintw(game_win, 7, 2, "[Dumb AI] Dealer shot live!");
        playerHealth = std::max(playerHealth - 20, 0);
    } else {
        mvwprintw(game_win, 7, 2, "[Dumb AI] Dealer shot blank.");
    }
}

// Scope-Aware AI: If dealer knows the shell, act accordingly
void dealerScopeAware(WINDOW *game_win, int &playerHealth, bool currentShell) {
    if (currentShell) {
        mvwprintw(game_win, 7, 2, "[Scope-Aware AI] Dealer knows it's live! Attacking.");
        playerHealth = std::max(playerHealth - 20, 0);
    } else {
        mvwprintw(game_win, 7, 2, "[Scope-Aware AI] Dealer knows it's blank. Skipping.");
    }
}

// Risk-Aware AI: Attack only if risk is reasonable
void dealerRiskAware(WINDOW *game_win, int &playerHealth, int dealerHealth, int liveCount, int totalShells) {
    float risk = totalShells > 0 ? (float)liveCount / totalShells : 0;
    if (dealerHealth < 20 && risk > 0.6) {
        mvwprintw(game_win, 7, 2, "[Risk-Aware AI] Dealer too weak, skipped shooting.");
        return;
    }
    if (risk > 0.4 || rand() % 2 == 1) {
        mvwprintw(game_win, 7, 2, "[Risk-Aware AI] Dealer decided to shoot.");
        playerHealth = std::max(playerHealth - 20, 0);
    } else {
        mvwprintw(game_win, 7, 2, "[Risk-Aware AI] Dealer skipped shooting.");
    }
}

// Smart AI: Combines risk and blood state
void dealerSmart(WINDOW *game_win, int &playerHealth, int dealerHealth, bool currentShell, int liveCount, int totalShells) {
    float risk = totalShells > 0 ? (float)liveCount / totalShells : 0;

    if (playerHealth <= 20 && (currentShell || risk > 0.5)) {
        mvwprintw(game_win, 7, 2, "[Smart AI] Player weak, Dealer tries to finish!");
        playerHealth = std::max(playerHealth - 20, 0);
        return;
    }

    if (dealerHealth <= 20 && risk > 0.5) {
        mvwprintw(game_win, 7, 2, "[Smart AI] Dealer avoids risky shooting.");
        return;
    }

    if (currentShell || risk > 0.5 || rand() % 2 == 1) {
        mvwprintw(game_win, 7, 2, "[Smart AI] Dealer attacked smartly.");
        playerHealth = std::max(playerHealth - 20, 0);
    } else {
        mvwprintw(game_win, 7, 2, "[Smart AI] Dealer skipped.");
    }
}

// 总调度器
void dealerAI(WINDOW *game_win, int &playerHealth, int &dealerHealth, bool currentShell, int liveCount, int totalShells, DealerAILevel aiLevel) {
    switch (aiLevel) {
        case DUMB:
            dealerDumb(game_win, playerHealth);
            break;
        case SCOPE_AWARE:
            dealerScopeAware(game_win, playerHealth, currentShell);
            break;
        case RISK_AWARE:
            dealerRiskAware(game_win, playerHealth, dealerHealth, liveCount, totalShells);
            break;
        case SMART:
            dealerSmart(game_win, playerHealth, dealerHealth, currentShell, liveCount, totalShells);
            break;
    }
    wrefresh(game_win); // 保证AI出手信息刷新出来
}
