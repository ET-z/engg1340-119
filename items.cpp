
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include<ncurses.h>

using namespace std;

extern vector<int> shells; 
extern Player player;
extern Opponent opponent;

//suggested player class:
//class Player {
//public:
    // Member Variables
 //   std::vector<std::string> items; // Inventory of items
 //   int health;                     // Player's health
 //   bool isTurn;                    // Whether it's the player's turn
 //   bool isDealer;                  // Whether the player is the dealer
//handcuff 里面的turn逻辑可能有点问题
//functions needed: player.takeDamage(int damage),player.health, opponent.isTurn,items.erase(),a structure named Player
// Function to erase an item from the inventory window
void erase_in_inventory(WINDOW *subWindow) {
    if (!subWindow) {
        std::cerr << "Error: Invalid subWindow pointer." << std::endl;
        return;
    }
    // Clear the sub-window
    wclear(subWindow);

    // Redraw the box for the sub-window
    box(subWindow, 0, 0);

    // Refresh the sub-window to reflect the changes
    wrefresh(subWindow);
}
//  the player is the person using knife now
void Knife(vector<int> &shells, Player &player,Player &opponent,const std::vector<std::vector<WINDOW*>>& dealerWindows,const std::vector<std::vector<WINDOW*>>& playerWindows) {
    auto it = find(player.items.begin(), player.items.end(), "knife");
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        int win_row;
        int win_col;
        win_row=position/4;
        win_col=position%4;
        // Remove the knife from the player's inventory
        player.items.erase(it);
        //erase it from the player window or dealer window
        if (!player.isDealer){
            erase_in_inventory(playerWindows[win_row][win_col]);
        }
        else if (player.isDealer){
            erase_in_inventory(dealerWindows[win_row][win_col]);
        }
        cout << "Knife found! Doubling the damage..." << endl;
        if (!shells.empty()) {
            int currentShell = shells[0]; // assuming the first shell is the current one
            if (currentShell == 1) {
                cout << "Doubling the damage.....!" << endl;
                opponent.takeDamage(40);
                cout << "Opponent's remaining health -40 " <<  endl;
            } else {
                cout << "The current shell is blank." << endl;
            }
        }  
    } 
    else{
        cout<<"No knife found"<<endl;
    }

}


void magnifyingGlass(vector<int> &shells, Player &player,const std::vector<std::vector<WINDOW*>>& dealerWindows,const std::vector<std::vector<WINDOW*>>& playerWindows) {
    // checking 
    auto it = find(player.items.begin(), player.items.end(), "magnifyingGlass");
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        int win_row;
        int win_col;
        win_row=position/4;
        win_col=position%4;
        // erase the magnifying glass from the player's items
        player.items.erase(it);
        //erase it from the player or dealer window
        if (!player.isDealer){
            erase_in_inventory(playerWindows[win_row][win_col]);
        }
        else if (player.isDealer){
            erase_in_inventory(dealerWindows[win_row][win_col]);
        }

        // reveal the current shell
        if (!shells.empty()) {
            int currentShell = shells[0]; // assuming the first shell is the current one
            if (currentShell == 1) {
                cout << "The current shell is live!"<<endl;
            } else {
                cout << "The current shell is blank." << endl;
            }
        } else {
            cout << "There are no shells left." << endl;
        }
    } else {
        cout << "You don't have a magnifying glass." << endl;
    }
}
//1. need a int vector to represent the current shells
//need player.items be a vector, player should be a struct 
//only checks player, how about using it for dealer

void handcuff(vector<int> &shells, Player &player,Player &opponent, const std::vector<std::vector<WINDOW*>>& dealerWindows,const std::vector<std::vector<WINDOW*>>& playerWindows) {
    // check
    auto it = find(player.items.begin(), player.items.end(), "handcuff");
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        int win_row;
        int win_col;
        win_row=position/4;
        win_col=position%4;
        // remove
        player.items.erase(it);
        //erase it from the player or dealer window
        if (!player.isDealer){
            erase_in_inventory(playerWindows[win_row][win_col]);
        }
        else if (player.isDealer){
            erase_in_inventory(dealerWindows[win_row][win_col]);
        }
       
        // save
        bool currentTurn = player.isTurn;

        // skip
        cout << "You used handcuff! The opponent is restrained for one turn." << endl;

        // resume
        player.isTurn = currentTurn;
        opponent.isTurn = !currentTurn;
    } else {
        cout << "You don't have handcuff." << endl;
    }
}


void apple(vector<int> &shells, Player &player,const std::vector<std::vector<WINDOW*>>& dealerWindows,const std::vector<std::vector<WINDOW*>>& playerWindows) {
    // check
    auto it = find(player.items.begin(), player.items.end(), "apple");
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        int win_row;
        int win_col;
        win_row=position/4;
        win_col=position%4;
        // remove
        player.items.erase(it);
        //erase it from the player or dealer window
        if (!player.isDealer){
            erase_in_inventory(playerWindows[win_row][win_col]);
        }
        else if (player.isDealer){
            erase_in_inventory(dealerWindows[win_row][win_col]);
        }

        // increase
        player.health += 1;
        cout << "You ate an apple! Your health increased by 1. Current health: " << player.health << endl;
    } else {
        cout << "You don't have a apple." << endl;
    }
}

void beer(vector<int> &shells, Player &player,const std::vector<std::vector<WINDOW*>>& dealerWindows,const std::vector<std::vector<WINDOW*>>& playerWindows) {
    // check
    auto it = find(player.items.begin(), player.items.end(), "beer");
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        int win_row;
        int win_col;
        win_row=position/4;
        win_col=position%4;
        // remove
        player.items.erase(it);
        //erase it from the player or dealer window
        if (!player.isDealer){
            erase_in_inventory(playerWindows[win_row][win_col]);
        }
        else if (player.isDealer){
            erase_in_inventory(dealerWindows[win_row][win_col]);
        }

        // check
        if (!shells.empty()) {
            // remove
            int removedShell = shells[0];
            shells.erase(shells.begin());

            // force
            cout << "You drank beer and fired a shot!" << endl;
            if (removedShell == 1) {
                // hurt
                player.takeDamage(20);
                cout << "It was a live shell! You took 20 damage. Current health: " << player.health << endl;
            } else {
                // empty
                cout << "It was a blank shell. Phew!" << endl;
            }
        } else {
            cout << "There are no shells left." << endl;
        }
    } else {
        cout << "You don't have beer." << endl;
    }
}

// needed functions or menbers: player.health,player.takeDemage()

