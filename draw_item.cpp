#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include "game.h"
using namespace std;

// draw handcuff
void draw_handcuff(WINDOW *items_draw, int y, int x)
{
    vector<string> art = {
        "  .--.      .--.  ",
        " /--\\ \\.--./ /--\\ ",
        "(    ) )   ( (   )",
        " \\__/ /'--'\\ \\__/ ",
        "  '--'      '--'  "};
    for (size_t i = 0; i < art.size(); i++)
    {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

// draw apple
void draw_apple(WINDOW *items_draw, int y, int x)
{
    vector<string> art = {
        "     ,--./,-.    ",
        "    / #      \\   ",
        "   |          |  ",
        "    \\        /   ",
        "     `._,._,'    "};
    for (size_t i = 0; i < art.size(); i++)
    {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

// draw knife
void draw_knife(WINDOW *items_draw, int y, int x)
{
    vector<string> art = {
        "emmmmmm~~~~~~~~~oT",
        "\"\"\"\"\"|      |",
        "      |          |",
        "      `----------'"};
    for (size_t i = 0; i < art.size(); i++)
    {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

// draw manifying glass
void draw_magnifying_glass(WINDOW *items_draw, int y, int x)
{
    vector<string> art = {
        "         .-\"\"-.  ",
        " _______/      \\  ",
        "|_______         ; ",
        "        \\      /  ",
        "         '-..-'"};
    for (size_t i = 0; i < art.size(); i++)
    {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

// draw beer
void draw_beer(WINDOW *items_draw, int y, int x)
{
    vector<string> art = {
        ".~~~~~~.",
        "i=======i_",
        "|ccccccc| \\",
        "|ccccccc|_/",
        "|ccccccc|   ",
        "`-=====-'"};
    for (size_t i = 0; i < art.size(); i++)
    {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

string get_item_description(string item)
{
    // add description
    if (item == "handcuff")
    {
        return "restrain the dealer for one round";
    }
    else if (item == "apple")
    {
        return "gain an extra heart";
    }
    else if (item == "knife")
    {
        return "double the next bullet damage";
    }
    else if (item == "magnifyingGlass")
    {
        return "check current bullet";
    }
    else if (item == "beer")
    {
        return "eject current shell";
    }
    else
    {
        return "unknown item";
    }
}

void draw_dealer_Items(Player &dealer, const std::vector<std::vector<WINDOW *>> &dealerWindows)
{
    // initialize colorpair
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    // Draw dealer items in dealer inventory windows
    for (int i = 0; i < 8; ++i)
    {
        int row = (i - i % 4) / 4;
        int col = i % 4;
        // Clear the dealer inventory window
        wclear(dealerWindows[row][col]);
        int HEIGHT, WIDTH;
        getmaxyx(dealerWindows[row][col], HEIGHT, WIDTH);

        // clean
        werase(dealerWindows[row][col]);

        // box
        box(dealerWindows[row][col], 0, 0);
        // declare current item
        string item = dealer.items[i];

        // color
        wattron(dealerWindows[row][col], COLOR_PAIR(3));
        // start position
        int start_y = 2;
        int start_x = 2;
        // name and tutorial
        mvwprintw(dealerWindows[row][col], start_y, start_x, "%s", item.c_str());
        mvwprintw(dealerWindows[row][col], start_y + 1, start_x, "Used to %s", get_item_description(item).c_str());
        // draw items accordingly
        start_y = 4;
        if (item == "handcuff")
        {
            draw_handcuff(dealerWindows[row][col], start_y, start_x);
        }
        else if (item == "apple")
        {
            draw_apple(dealerWindows[row][col], start_y, start_x);
        }
        else if (item == "knife")
        {
            draw_knife(dealerWindows[row][col], start_y, start_x);
        }
        else if (item == "magnifyingGlass")
        {
            draw_magnifying_glass(dealerWindows[row][col], start_y, start_x);
        }
        else if (item == "beer")
        {
            draw_beer(dealerWindows[row][col], start_y, start_x);
        }

        wattroff(dealerWindows[row][col], COLOR_PAIR(3));

        // Refresh the dealer inventory window to display the item
        wrefresh(dealerWindows[row][col]);
    }
}

void draw_player_Items(Player &player, const std::vector<std::vector<WINDOW *>> &playerWindows)
{
    // initialize colorpair
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    // Draw player items in player inventory windows
    for (int i = 0; i < 8; ++i)
    {
        int row = (i - i % 4) / 4;
        int col = i % 4;
        // Clear the player inventory window
        wclear(playerWindows[row][col]);
        int HEIGHT, WIDTH;
        getmaxyx(playerWindows[row][col], HEIGHT, WIDTH);

        // clean
        werase(playerWindows[row][col]);

        // box
        box(playerWindows[row][col], 0, 0);
        // declare current item
        string item = player.items[i];

        // color
        wattron(playerWindows[row][col], COLOR_PAIR(3));
        // start position
        int start_y = 2;
        int start_x = 2;
        // name and tutorial
        mvwprintw(playerWindows[row][col], start_y, start_x, "%s", item.c_str());
        mvwprintw(playerWindows[row][col], start_y + 1, start_x, "Used to %s", get_item_description(item).c_str());
        // draw items accordingly
        start_y = 4;
        if (item == "handcuff")
        {
            draw_handcuff(playerWindows[row][col], start_y, start_x);
        }
        else if (item == "apple")
        {
            draw_apple(playerWindows[row][col], start_y, start_x);
        }
        else if (item == "knife")
        {
            draw_knife(playerWindows[row][col], start_y, start_x);
        }
        else if (item == "magnifyingGlass")
        {
            draw_magnifying_glass(playerWindows[row][col], start_y, start_x);
        }
        else if (item == "beer")
        {
            draw_beer(playerWindows[row][col], start_y, start_x);
        }

        wattroff(playerWindows[row][col], COLOR_PAIR(3));

        // Refresh the dealer inventory window to display the item
        wrefresh(playerWindows[row][col]);
    }
}
