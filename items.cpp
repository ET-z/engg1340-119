#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

extern vector<int> shells; 
extern Player player;
extern Opponent opponent;

int double=1
void useKnife(vector<int> shell, Player player, int& double) {
    // Check if the player has the "knife" item
    bool hasKnife = false;
    for (const string& item : player.items) {
        if (item == "knife") {
            hasKnife = true;
            break;
        }
    }

    // Apply double damage if the player has the knife
    if (hasKnife) {
        cout << "Knife found! Doubling the damage..." << endl;
        double=2; // Double damage
    } 
    else{
        cout<<"No knife found"<<endl;
    }

    // Output the opponent's remaining health
    cout << "Opponent's remaining health: " << health << endl;
}
//after shooting, reset double to 1
int double=1

void magnifyingGlass(vector<string>shells,) {
    // checking 
    auto it = find(player.items.begin(), player.items.end(), "magnifyingGlass");
    if (it != player.items.end()) {
        // erase the magnifying glass from the player's items
        player.items.erase(it);

        // reveal the current shell
        if (!shells.empty()) {
            int currentShell = shells[0]; // assuming the first shell is the current one
            if (currentShell == 1) {
                cout << "The current shell is live!" << endl;
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

