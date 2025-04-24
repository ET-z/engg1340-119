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
//only checks player, how about using it for deale


void handcuff() {
    // Find the item "handcuff" in the player's items
    auto it = find(player.items.begin(), player.items.end(), "handcuff");
    // Check if the item is found
    if (it != player.items.end()) {
        // Calculate the position of the item in the items vector
        int position = distance(player.items.begin(), it);
        // Calculate the row position for winning
        win_row = position / 4;
        // Calculate the column position for winning
        win_col = position % 4;
        // Remove the item from the player's items
        player.items.erase(it);
       
        // Save the current player's turn status
        bool currentTurn = player.isTurn;

        // Get the window dimensions
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        // Display message in the middle of the screen
        mvprintw(rows / 2, (cols - strlen("You used handcuff! The opponent is restrained for one turn.")) / 2,
                 "You used handcuff! The opponent is restrained for one turn.");

        // Restore the player's turn status
        player.isTurn = currentTurn;
        // Set the opponent's turn status to the opposite of the player's
        opponent.isTurn = !currentTurn;
    } else {
        // Get the window dimensions
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        // Display message in the middle of the screen
        mvprintw(rows / 2, (cols - strlen("You don't have handcuff.")) / 2,
                 "You don't have handcuff.");
    }
    // Refresh the screen to display the changes
    refresh();
}

void apple() {
    // Find the item "apple" in the player's items
    auto it = find(player.items.begin(), player.items.end(), "apple");
    // Check if the item is found
    if (it != player.items.end()) {
        // Calculate the position of the item in the items vector
        int position = distance(player.items.begin(), it);
        // Calculate the row position for winning
        win_row = position / 4;
        // Calculate the column position for winning
        win_col = position % 4;
        // Remove the item from the player's items
        player.items.erase(it);

        // Increase the player's health
        player.health += 1;

        // Get the window dimensions
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        // Create a message string with the updated health
        char message[100];
        snprintf(message, sizeof(message), "You smoked a apple! Your health increased by 1. Current health: %d", player.health);

        // Display message in the middle of the screen
        mvprintw(rows / 2, (cols - strlen(message)) / 2, message);
    } else {
        // Get the window dimensions
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        // Display message in the middle of the screen
        mvprintw(rows / 2, (cols - strlen("You don't have a apple.")) / 2,
                 "You don't have a apple.");
    }
    // Refresh the screen to display the changes
    refresh();
}

void beer() {
    // Find the item "beer" in the player's items
    auto it = find(player.items.begin(), player.items.end(), "beer");
    // Check if the item is found
    if (it != player.items.end()) {
        // Calculate the position of the item in the items vector
        int position = distance(player.items.begin(), it);
        // Calculate the row position for winning
        win_row = position / 4;
        // Calculate the column position for winning
        win_col = position % 4;
        // Remove the item from the player's items
        player.items.erase(it);

        // Check if there are shells available
        if (!shells.empty()) {
            // Remove the first shell from the shells vector
            int removedShell = shells[0];
            shells.erase(shells.begin());

            // Get the window dimensions
            int rows, cols;
            getmaxyx(stdscr, rows, cols);

            // Display message in the middle of the screen
            mvprintw(rows / 2, (cols - strlen("You drank beer and fired a shot!")) / 2,
                     "You drank beer and fired a shot!");

            // Check if the removed shell is live
            if (removedShell == 1) {
                // Decrease the player's health
                player.takeDamage(20);

                // Create a message string with the updated health
                char message[100];
                snprintf(message, sizeof(message), "It was a live shell! You took 20 damage. Current health: %d", player.health);

                // Display message below the previous one
                mvprintw(rows / 2 + 1, (cols - strlen(message)) / 2, message);
            } else {
                // Display message below the previous one
                mvprintw(rows / 2 + 1, (cols - strlen("It was a blank shell. Phew!")) / 2,
                         "It was a blank shell. Phew!");
            }
        } else {
            // Get the window dimensions
            int rows, cols;
            getmaxyx(stdscr, rows, cols);

            // Display message in the middle of the screen
            mvprintw(rows / 2, (cols - strlen("There are no shells left.")) / 2,
                     "There are no shells left.");
        }
    } else {
        // Get the window dimensions
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        // Display message in the middle of the screen
        mvprintw(rows / 2, (cols - strlen("You don't have beer.")) / 2,
                 "You don't have beer.");
    }
    // Refresh the screen to display the changes
    refresh();
}
