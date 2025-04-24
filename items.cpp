#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iterator>

using namespace std;

extern vector<int> shells; 
extern Player player;
extern Opponent opponent;

//functions needed: player.takeDamage(int damage),player.health, opponent.isTurn,items.erase(),a structure named Player
// Function to erase an item from the inventory window
void erase_in_inventory(WINDOW *subWindow) {
    // Clear the sub-window
    wclear(subWindow);

    // Redraw the box for the sub-window
    box(subWindow, 0, 0);

    // Refresh the sub-window to reflect the changes
    wrefresh(subWindow);
}
void Knife(vector<int> shell, Player player) {
    auto it = find(player.items.begin(), player.items.end(), "knife");
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        win_row=position/4;
        win_col=position%4;
        // Remove the knife from the player's inventory
        player.items.erase(it);
        cout << "Knife found! Doubling the damage..." << endl;
        if (!shells.empty()) {
            int currentShell = shells[0]; // assuming the first shell is the current one
            if (currentShell == 1) {
                cout << "Doubling the demage.....!" << endl;
                player.takeDamage(40);
                cout << "Opponent's remaining health: " << health << endl;
            } else {
                out << "The current shell is blank." << endl;
            }
        }  
    } 
    else{
        cout<<"No knife found"<<endl;
    }

    // Output the opponent's remaining health
    cout << "Opponent's remaining health: " << health << endl;
}


void magnifyingGlass(vector<string>shells) {
    // checking 
    auto it = find(player.items.begin(), player.items.end(), "magnifyingGlass");
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        win_row=position/4;
        win_col=position%4;
        // erase the magnifying glass from the player's items
        player.items.erase(it);

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

void handcuff() {
    // check
    auto it = find(player.items.begin(), player.items.end(), "handcuff");
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        win_row=position/4;
        win_col=position%4;
        // remove
        player.items.erase(it);
       
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


void apple() {
    // check
    auto it = find(player.items.begin(), player.items.end(), "apple");
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        win_row=position/4;
        win_col=position%4;
        // remove
        player.items.erase(it);

        // increase
        player.health += 1;
        cout << "You smoked a apple! Your health increased by 1. Current health: " << player.health << endl;
    } else {
        cout << "You don't have a apple." << endl;
    }
}

void beer() {
    // check
    auto it = find(player.items.begin(), player.items.end(), "beer");
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        win_row=position/4;
        win_col=position%4;
        // remove
        player.items.erase(it);

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
