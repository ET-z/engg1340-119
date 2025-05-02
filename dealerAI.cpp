#include "dealerAI.h"
#include <cstdlib>
#include <string>
#include <algorithm>
#include <random>

void printCentere(WINDOW *win, const std::string &message, int y_center)
{
    int HEIGHT, WIDTH;
    getmaxyx(win, HEIGHT, WIDTH);

    int x_center = (WIDTH - message.length()) / 2;

    mvwprintw(win, y_center, x_center, "%s", message.c_str());
    wrefresh(win);
}

// Dumb AI: Always attack
void dealerDumb(WINDOW *game_win, int &playerHealth, bool &currentShell, int &dealerDamage)
{
    if (currentShell)
    {
        printCentere(game_win, "[Dumb AI] Dealer shot live!", 25);
        napms(3000);
        playerHealth = std::max(playerHealth - dealerDamage, 0);
        dealerDamage = 20;
        dealerTurn = false;
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
        dealerTurn = false;
        napms(3000);
        return;
    }
}

// Scope-Aware AI: If dealer knows the shell, act accordingly
void dealerScopeAware(WINDOW *game_win, int &playerHealth, bool currentShell, int &dealerDamage)
{
    if (currentShell)
    {
        printCentere(game_win, "[Scope-Aware AI] Dealer knows it's live! Attacking.", 25);
        napms(3000);
        playerHealth = std::max(playerHealth - dealerDamage, 0);
        dealerDamage = 20;
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
        return;
    }
}

// Risk-Aware AI: Attack only if risk is reasonable
void dealerRiskAware(WINDOW *game_win, int &playerHealth, int &dealerHealth, int &liveCount, int &totalShells, bool &currentShell, bool &playerTurn, int &dealerDamage, bool &dealerTurn)
{
    srand(time(0));
    int risk = rand() % 2;
    if (risk == 1)
    {
        printCentere(game_win, "[Random AI] Dealer decided to shoot you.", 25);
        wclear(game_win);
        box(game_win, 0, 0);
        napms(2000);
        if (currentShell)
        {
            printCentere(game_win, "[Random AI] Dealer shot live!", 25);
            napms(3000);
            playerHealth = std::max(playerHealth - dealerDamage, 0);
            dealerDamage = 20;
            dealerTurn = false;
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
            printCentere(game_win, "[Random AI] Dealer shot blank!", 25);
            dealerTurn = false;
            napms(3000);
            return;
        }
    }
    else
    {
        printCentere(game_win, "[Random AI] Dealer decided to shoot himself", 25);
        wclear(game_win);
        box(game_win, 0, 0);
        napms(2000);
        if (currentShell)
        {
            printCentere(game_win, "[Random AI] Dealer shot live!", 25);
            napms(3000);
            dealerTurn = false;
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
            printCentere(game_win, "[Random AI] Dealer shot blank!", 25);
            dealerTurn = true;
            napms(3000);
            return;
        }
    }
}

// Smart AI: Combines risk and blood state
void dealerSmart(WINDOW *game_win, int &playerHealth, int &dealerHealth, bool &currentShell, int &liveCount, int &totalShells, bool &playerTurn, int &dealerDamage, bool &dealerTurn)
{
    float risk = totalShells > 0 ? (float)liveCount / totalShells : 0;

    if (risk > 0.5)
    {
        printCentere(game_win, "[Smart AI] Dealer wants blood! He shoots you.", 25);
        wclear(game_win);
        box(game_win, 0, 0);
        napms(2000);
        if (currentShell)
        {
            printCentere(game_win, "[Smart AI] Dealer shot live!", 25);
            napms(3000);
            dealerTurn = false;
            playerHealth = std::max(playerHealth - dealerDamage, 0);
            dealerDamage = 20;
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
            printCentere(game_win, "[Smart AI] Dealer shot blank!", 25);
            dealerTurn = false;
            napms(3000);
            return;
        }
        return;
    }
    else
    {
        printCentere(game_win, "[Smart AI] Dealer shoots himself!", 25);
        wclear(game_win);
        box(game_win, 0, 0);
        napms(2000);
        if (currentShell)
        {
            printCentere(game_win, "[Smart AI] Dealer shot live!", 25);
            napms(3000);
            dealerTurn = false;
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
            napms(3000);
            dealerTurn = true;
            return;
        }
        return;
    }
}

void dealerAI(WINDOW *game_win, int &playerHealth, int &dealerHealth, bool &currentShell, int &liveCount, int &totalShells, DealerAILevel aiLevel, bool &playerTurn, int &dealerDamage, bool &dealerTurn)
{
    switch (aiLevel)
    {
    case DUMB:
        dealerDumb(game_win, playerHealth, currentShell, dealerDamage);
        break;
    case SCOPE_AWARE:
        dealerScopeAware(game_win, playerHealth, currentShell, dealerDamage);
        break;
    case RISK_AWARE:
        dealerRiskAware(game_win, playerHealth, dealerHealth, liveCount, totalShells, currentShell, playerTurn, dealerDamage, dealerTurn);
        break;
    case SMART:
        dealerSmart(game_win, playerHealth, dealerHealth, currentShell, liveCount, totalShells, playerTurn, dealerDamage, dealerTurn);
        break;
    }
    wrefresh(game_win);
}
