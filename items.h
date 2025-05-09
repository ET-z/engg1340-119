#ifndef ITEMS_H
#define ITEMS_H

#include <vector>
#include <string>
#include <ncurses.h>
#include <utility>

class Player; // Forward declaration since Player class is defined elsewhere

// Function to erase an item from the inventory window
void erase_in_inventory(WINDOW *subWindow);

// Function to use knife item
void Knife(std::vector<int> &shells, Player &player, Player &opponent, const std::vector<std::vector<WINDOW *>> &dealerWindows, const std::vector<std::vector<WINDOW *>> &playerWindows);

// Function to use magnifying glass item
void magnifyingGlass(std::vector<int> &shells, Player &player, const std::vector<std::vector<WINDOW *>> &dealerWindows, const std::vector<std::vector<WINDOW *>> &playerWindows);

// Function to use handcuff item
void handcuff(std::vector<int> &shells, Player &player, const std::vector<std::vector<WINDOW *>> &dealerWindows, const std::vector<std::vector<WINDOW *>> &playerWindows);

// Function to use apple item
void apple(std::vector<int> &shells, Player &player, const std::vector<std::vector<WINDOW *>> &dealerWindows, const std::vector<std::vector<WINDOW *>> &playerWindows);

// Function to use beer item
void beer(std::vector<int> &shells, Player &player, const std::vector<std::vector<WINDOW *>> &dealerWindows, const std::vector<std::vector<WINDOW *>> &playerWindows);

void draw_item(WINDOW *item_draw, std::string item);

void random_items(std::vector<std::vector<std::string>> *inventory, int seed_offset = 0);
std::pair<int, int> use_random_item(std::vector<std::vector<std::string>> *inventory);

#endif // ITEMS_H