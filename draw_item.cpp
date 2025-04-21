#include<iostream>
#include<random>
#include<string>
#include<ncurses.h>
#include<vector>
using namespace std;
// we suppose that the pick_Up items is done and it will generate two strings, dealerItems[8], and playerItems[8], containing the items
void drawItems(const std::string dealerItems[8], const std::string playerItems[8], const std::vector<std::vector<WINDOW*>>& dealerWindows, const std::vector<std::vector<WINDOW*>>& playerWindows) {
    // Draw dealer items in dealer inventory windows
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 4; col++) {
            // Clear the dealer inventory window
            wclear(dealerWindows[row][col]);
            
            // Print the dealer item name in the dealer inventory window
            mvwprintw(dealerWindows[row][col], 1, 1, dealerItems[row * 4 + col].c_str());
            
            // Refresh the dealer inventory window to display the item
            wrefresh(dealerWindows[row][col]);
        }
    }

    // Draw player items in player inventory windows
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 4; col++) {
            // Clear the player inventory window
            wclear(playerWindows[row][col]);
            
            // Print the player item name in the player inventory window
            mvwprintw(playerWindows[row][col], 1, 1, playerItems[row * 4 + col].c_str());
            
            // Refresh the player inventory window to display the item
            wrefresh(playerWindows[row][col]);
        }
    }
}
