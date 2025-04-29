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
//functions needed: player.takeDamage(int damage),player.health, opponent.isTurn,items.erase,a structure named Player
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
        int rows, cols;
        getmaxyx(stdscr, rows, cols);
        mvprintw(rows / 2, (cols - strlen("Doubling the damage.....!"))/2,"Doubling the damage.....!")
        if (!shells.empty()) {
            int currentShell = shells[0]; // assuming the first shell is the current one
            if (currentShell == 1) {
                mvprintw(rows / 2, (cols - strlen("Doubling the damage.....!"))/2,"Doubling the damage.....!");

                opponent.takeDamage(40);
                mvprintw(rows / 2, (cols - strlen("Opponent's remaining health -40 "))/2,"Opponent's remaining health -40 ");

            } else {
                mvprintw(rows / 2, (cols - strlen("The current shell is blank."))/2,"The current shell is blank.");

            }
        }  
    } 
    else{
        int rows,cols;
        getmaxyx(stdscr, rows, cols);
        mvprintw(rows / 2, (cols - strlen("You don't have a knife! "))/2,"You don't have a knife! ");
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
            int rows, cols;
            getmaxyx(stdscr, rows, cols);
            if (currentShell == 1) {
                mvprintw(rows / 2, (cols - strlen("The current shell is live!"))/2,"The current shell is live!");
            } else {
                mvprintw(rows / 2, (cols - strlen("The current shell is blank."))/2,"The current shell is blank.");
            }
        } else {
            mvprintw(rows / 2, (cols - strlen("There are no shells left."))/2,"There are no shells left.");
        }
    } else {
        mvprintw(rows / 2, (cols - strlen("You don't have a magnifying glass."))/2,"You don't have a magnifying glass.");
    }
}
//1. need a int vector to represent the current shells
//need player.items be a vector, player should be a struct 
//only checks player, how about using it for dealer


void handcuff(vector<int> &shells, Player &player,const std::vector<std::vector<WINDOW*>>& dealerWindows,const std::vector<std::vector<WINDOW*>>& playerWindows) {
    // Find the item "handcuff" in the player's items
    auto it = find(player.items.begin(), player.items.end(), "handcuff");
    // Check if the item is found
    if (it != player.items.end()) {
        // Calculate the position of the item in the items vector
        int position = distance(player.items.begin(), it);
        int win_row;
        int win_col;
        win_row=position/4;
        win_col=position%4;
        player.items.erase(it);
        if (!player.isDealer){
            erase_in_inventory(playerWindows[win_row][win_col]);
        }
        else if (player.isDealer){
            erase_in_inventory(dealerWindows[win_row][win_col]);
        }
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

void apple(vector<int> &shells, Player &player,const std::vector<std::vector<WINDOW*>>& dealerWindows,const std::vector<std::vector<WINDOW*>>& playerWindows) {
    // Find the item "apple" in the player's items
    auto it = find(player.items.begin(), player.items.end(), "apple");
    // Check if the item is found
    if (it != player.items.end()) {
        // Calculate the position of the item in the items vector
        int position = distance(player.items.begin(), it);
        int win_row;
        int win_col;
        win_row=position/4;
        win_col=position%4;
        player.items.erase(it);
        if (!player.isDealer){
            erase_in_inventory(playerWindows[win_row][win_col]);
        }
        else if (player.isDealer){
            erase_in_inventory(dealerWindows[win_row][win_col]);
        }

        // Increase the player's health
        player.health += 20;

        // Get the window dimensions
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        // Create a message string with the updated health
        char message[100];
        snprintf(message, sizeof(message), "You ate an apple! Your health increased by 20. Current health: %d", player.health);

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

void beer(vector<int> &shells, Player &player, const std::vector<std::vector<WINDOW*>>& dealerWindows, const std::vector<std::vector<WINDOW*>>& playerWindows) {
    // Find the item "beer" in the player's items
    auto it = find(player.items.begin(), player.items.end(), "beer");
    
    // Check if the item is found
    if (it != player.items.end()) {
        int position = distance(player.items.begin(), it);
        int win_row = position / 4;
        int win_col = position % 4;
        
        // Remove beer from inventory
        player.items.erase(it);
        
        if (!player.isDealer) {
            erase_in_inventory(playerWindows[win_row][win_col]);
        } else if (player.isDealer) {
            erase_in_inventory(dealerWindows[win_row][win_col]);
        }

        // Check if there are shells available
        if (!shells.empty()) {
            // Remove the first shell from the shells vector
            shells.erase(shells.begin());
            
            // Get window dimensions
            int rows, cols;
            getmaxyx(stdscr, rows, cols);
            
            // Display message in the middle of the screen
            mvprintw(rows / 2, (cols - strlen("You used beer to eject a shell")) / 2,
                     "You used beer to eject a shell");
        } else {
            // Get window dimensions
            int rows, cols;
            getmaxyx(stdscr, rows, cols);
            
            // Display message in the middle of the screen
            mvprintw(rows / 2, (cols - strlen("There are no shells left.")) / 2,
                     "There are no shells left.");
        }
    } else {
        // Get window dimensions
        int rows, cols;
        getmaxyx(stdscr, rows, cols);
        
        // Display message in the middle of the screen
        mvprintw(rows / 2, (cols - strlen("You don't have beer.")) / 2,
                 "You don't have beer.");
    }

    // Refresh the screen to display the changes
    refresh();
}

// needed functions or menbers: player.health,player.takeDemage()

