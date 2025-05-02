#include "dealerAI.h"
#include <cstdlib>
#include <string>
#include <algorithm>

void printCentere(WINDOW *win, const std::string &message, int y_center)
{
    int HEIGHT, WIDTH;
    getmaxyx(win, HEIGHT, WIDTH);

    int x_center = (WIDTH - message.length()) / 2;

    mvwprintw(win, y_center, x_center, "%s", message.c_str());
    wrefresh(win);
}

// Dumb AI: Always attack
void dealerDumb(WINDOW *game_win, int &playerHealth, bool currentShell)
{

    if (currentShell)
    {
        printCentere(game_win, "[Dumb AI] Dealer shot live!", 25);
        napms(3000);
        playerHealth = std::max(playerHealth - 20, 0);
        // check if players health has dropped to 0 or below
        if (playerHealth <= 0)
        {
            printCentere(game_win, "Game Over! Dealer wins!", 26);
            napms(3000);
            return;
        }
    }
    else
    {
        printCentere(game_win, "[Dumb AI] Dealer shot blank.", 25);
        napms(3000);
    }
}

// Scope-Aware AI: If dealer knows the shell, act accordingly
void dealerScopeAware(WINDOW *game_win, int &playerHealth, bool currentShell)
{
    if (currentShell)
    {
        printCentere(game_win, "[Scope-Aware AI] Dealer knows it's live! Attacking.", 25);
        napms(3000);
        playerHealth = std::max(playerHealth - 20, 0);
        // check if players health has dropped to 0 or below
        if (playerHealth <= 0)
        {
            printCentere(game_win, "Game Over! Dealer wins!", 26);
            napms(3000);
            return;
        }
    }
    else
    {
        printCentere(game_win, "[Scope-Aware AI] Dealer knows it's blank. Skipping.", 25);
        napms(3000);
    }
}

// Risk-Aware AI: Attack only if risk is reasonable
void dealerRiskAware(WINDOW *game_win, int &playerHealth, int &dealerHealth, int liveCount, int totalShells, bool currentShell, bool &playerTurn, bool &dealerTurn)
{
    float risk = totalShells > 0 ? (float)liveCount / totalShells : 0;
    if (dealerHealth < 20 && risk > 0.6)
    {
        printCentere(game_win, "[Risk-Aware AI] Dealer too weak, decided to shoot you.", 25);
        if (currentShell)
        {
            printCentere(game_win, "[Risk-Aware AI] Dealer shot live!", 25);
            napms(3000);
            playerHealth = std::max(playerHealth - 20, 0);
            // check if players health has dropped to 0 or below
            if (playerHealth <= 0)
            {
                printCentere(game_win, "Game Over! Dealer wins!", 26);
                napms(3000);
                return;
            }
        }
        else
        {
            printCentere(game_win, "[Risk-Aware AI] Delear shot blank!", 25);
            napms(3000);
        }
    }
    else
    {
        printCentere(game_win, "[Risk-Aware AI] Dealer decided to shoot himself", 25);
        napms(3000);
        if (currentShell)
        {
            printCentere(game_win, "[Risk-Aware AI] Dealer shot live!", 25);
            napms(3000);
            dealerHealth = std::max(dealerHealth - 20, 0);
            // check if players health has dropped to 0 or below
            if (dealerHealth <= 0)
            {
                printCentere(game_win, "Game Over! You win!", 26);
                napms(3000);
                return;
            }
        }
        else
        {
            printCentere(game_win, "[Risk-Aware AI] Dealer shot blank!", 25);
            dealerTurn = true; // Keep it dealer's turn
            napms(3000);
        }
    }
}

// Smart AI: Combines risk and blood state
void dealerSmart(WINDOW *game_win, int &playerHealth, int &dealerHealth, bool currentShell, int liveCount, int totalShells, bool &playerTurn, bool &dealerTurn)
{
    float risk = totalShells > 0 ? (float)liveCount / totalShells : 0;

    if (playerHealth <= 20 && (risk > 0.5))
    {
        printCentere(game_win, "[Smart AI] Player weak, Dealer tries to finish!", 25);
        napms(3000);
        if (currentShell)
        {
            printCentere(game_win, "[Smart AI] Dealer shot live!", 25);
            napms(3000);
            playerHealth = std::max(playerHealth - 20, 0);
            // check if players health has dropped to 0 or below
            if (playerHealth <= 0)
            {
                printCentere(game_win, "Game Over! Dealer wins!", 26);
                napms(3000);
                return;
            }
        }
        else
        {
            printCentere(game_win, "[Smart AI] Delear shot blank!", 25);
            napms(3000);
        }
        return;
    }
    else if (dealerHealth <= 20 && risk > 0.5)
    {
        printCentere(game_win, "[Smart AI] Dealer avoids risky shooting himself.", 25);
        if (currentShell)
        {
            printCentere(game_win, "[Smart AI] Dealer shot live!", 25);
            napms(3000);
            playerHealth = std::max(playerHealth - 20, 0);
            // check if players health has dropped to 0 or below
            if (playerHealth <= 0)
            {
                printCentere(game_win, "Game Over! Dealer wins!", 26);
                napms(3000);
                return;
            }
        }
        else
        {
            printCentere(game_win, "[Smart AI] Delear shot blank!", 25);
            napms(3000);
        }
        napms(3000);
        return;
    }
    else
    {
        printCentere(game_win, "[Smart AI] Dealer shoots himself!", 25);
        if (currentShell)
        {
            printCentere(game_win, "[Smart AI] Dealer shot live!", 25);
            napms(3000);
            dealerHealth = std::max(dealerHealth - 20, 0);
            // check if players health has dropped to 0 or below
            if (dealerHealth <= 0)
            {
                printCentere(game_win, "Game Over! You wins", 26);
                napms(3000);
                return;
            }
        }
        else
        {
            printCentere(game_win, "[Smart AI] Dealer shot blank!", 25);
            dealerTurn = true; // Keep it dealer's turn
            napms(3000);
        }
        return;
    }
}

void dealerAI(WINDOW *game_win, int &playerHealth, int &dealerHealth, bool currentShell, int liveCount, int totalShells, DealerAILevel aiLevel, bool &playerTurn, bool &dealerTurn)
{
    switch (aiLevel)
    {
    case DUMB:
        dealerDumb(game_win, playerHealth, currentShell);
        break;
    case SCOPE_AWARE:
        dealerScopeAware(game_win, playerHealth, currentShell);
        break;
    case RISK_AWARE:
        dealerRiskAware(game_win, playerHealth, dealerHealth, liveCount, totalShells, currentShell, playerTurn, dealerTurn);
        break;
    case SMART:
        dealerSmart(game_win, playerHealth, dealerHealth, currentShell, liveCount, totalShells, playerTurn, dealerTurn);
        break;
    }
    wrefresh(game_win);
}
