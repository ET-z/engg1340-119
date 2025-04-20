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

