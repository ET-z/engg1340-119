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
        mvwprintw(items_draw, y + 1 + i, x, "%s", art[i].c_str());
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
        mvwprintw(items_draw, y + 1 + i, x, "%s", art[i].c_str());
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
        mvwprintw(items_draw, y + 2 + i, x, "%s", art[i].c_str());
    }
}

// draw manifying glass
void draw_magnifying_glass(WINDOW *items_draw, int y, int x)
{
    vector<string> art = {
        "         .-\"\"-.  ",
        " _______/      \\  ",
        "|_______        ; ",
        "        \\      /  ",
        "         '-..-'"};
    for (size_t i = 0; i < art.size(); i++)
    {
        mvwprintw(items_draw, y + 1 + i, x, "%s", art[i].c_str());
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
        mvwprintw(items_draw, y + i, x + 4, "%s", art[i].c_str());
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

void draw_item(WINDOW *item_draw, string item)
{
    // initialize colorpair
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    int start_y = 1;
    int start_x = 1;
    // Draw dealer items in dealer inventory windows
    if (item == "handcuff")
    {
        wattron(item_draw, COLOR_PAIR(3));
        draw_handcuff(item_draw, start_y, start_x);
        wattroff(item_draw, COLOR_PAIR(3));
    }
    else if (item == "apple")
    {
        wattron(item_draw, COLOR_PAIR(3));
        draw_apple(item_draw, start_y, start_x);
        wattroff(item_draw, COLOR_PAIR(3));
    }
    else if (item == "knife")
    {
        wattron(item_draw, COLOR_PAIR(3));
        draw_knife(item_draw, start_y, start_x);
        wattroff(item_draw, COLOR_PAIR(3));
    }
    else if (item == "magnifyingGlass")
    {
        wattron(item_draw, COLOR_PAIR(3));
        draw_magnifying_glass(item_draw, start_y, start_x);
        wattroff(item_draw, COLOR_PAIR(3));
    }
    else if (item == "beer")
    {
        wattron(item_draw, COLOR_PAIR(3));
        draw_beer(item_draw, start_y, start_x);
        wattroff(item_draw, COLOR_PAIR(3));
    }
    wrefresh(item_draw);
}
