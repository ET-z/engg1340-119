#include<iostream>
#include<random>
#include<string>
#include<ncurses.h>
#include<vector>
using namespace std;
#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include "game.h"
using namespace std;

// 手铐的字符画
void draw_handcuff(WINDOW *items_draw, int y, int x) {
    vector<string> art = {
        "  .--.      .--.  ",
        " /--\\ \\.--./ /--\\ ",
        "(    ) )   ( (   )",
        " \\__/ /'--'\\ \\__/ ",
        "  '--'      '--'  "
    };
    for (size_t i = 0; i < art.size(); i++) {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

// 香烟的字符画
void draw_cigarette(WINDOW *items_draw, int y, int x) {
    vector<string> art = {
        "     ,--./,-.    ",
        "    / #      \\   ",
        "   |          |  ",
        "    \\        /   ",
        "     `._,._,'    "
    };
    for (size_t i = 0; i < art.size(); i++) {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

// 小刀的字符画
void draw_knife(WINDOW *items_draw, int y, int x) {
    vector<string> art = {
        "emmmmmm~~~~~~~~~~oT",
        "\"\"\"\"\"|          |",
        "      |          |",
        "      `----------'"
    };
    for (size_t i = 0; i < art.size(); i++) {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

// 放大镜的字符画
void draw_magnifying_glass(WINDOW *items_draw, int y, int x) {
    vector<string> art = {
        " .-\"\"-. ",
        " _______/      \\  ",
        "|_______        ;",
        "        \\      /",
        "         '-..-'"
    };
    for (size_t i = 0; i < art.size(); i++) {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

// 啤酒的字符画
void draw_beer(WINDOW *items_draw, int y, int x) {
    vector<string> art = {
        ".~~~~~~.",
        "i=======i_",
        "|ccccccc| \\",
        "|ccccccc|_/",
        "|ccccccc|   ",
        "`-=====-'"
    };
    for (size_t i = 0; i < art.size(); i++) {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

// 肾上腺素的字符画
void draw_adrenaline(WINDOW *items_draw, int y, int x) {
    vector<string> art = {
        " ,________________________________       ",
        "|__________,----------._ [____]  \"\"-,__  __...-----===\"",
        "        (_(||||||||||||)___________/   \"\"             |",
        "           `----------'        [ ))\"-,                |",
        "                            \"\"    `,  _,--...___  |",
        "                                    `/          \"\"\""
    };
    for (size_t i = 0; i < art.size(); i++) {
        mvwprintw(items_draw, y + i, x, "%s", art[i].c_str());
    }
}

void draw_items(WINDOW *items_draw, vector<string> player_items) {
    int HEIGHT, WIDTH;
    getmaxyx(items_draw, HEIGHT, WIDTH);

    // 初始化颜色对
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

    // 清除窗口内容
    werase(items_draw);

    // 绘制边框
    box(items_draw, 0, 0);

    // 设置窗口标题
    mvwprintw(items_draw, 0, (WIDTH - string("Inventory").length()) / 2, "Inventory");

    // 计算道具起始位置
    int start_y = 2;
    int start_x = 2;

    // 绘制每个道具
    for (size_t i = 0; i < player_items.size(); i++) {
        string item = player_items[i];

        // 设置道具颜色
        wattron(items_draw, COLOR_PAIR(3));

        // 绘制道具名称和描述
        mvwprintw(items_draw, start_y, start_x, "%s", item.c_str());
        mvwprintw(items_draw, start_y + 1, start_x, "Used to %s", get_item_description(item).c_str());

        // 根据道具类型绘制对应的字符画
        int art_x = start_x + 20; // 调整字符画的起始x坐标
        if (item == "handcuff") {
            draw_handcuff(items_draw, start_y - 2, art_x);
        } else if (item == "cigarette") {
            draw_cigarette(items_draw, start_y - 2, art_x);
        } else if (item == "knife") {
            draw_knife(items_draw, start_y - 2, art_x);
        } else if (item == "magnifyingGlass") {
            draw_magnifying_glass(items_draw, start_y - 2, art_x);
        } else if (item == "beer") {
            draw_beer(items_draw, start_y - 2, art_x);
        } else if (item == "adrenaline") {
            draw_adrenaline(items_draw, start_y - 2, art_x);
        }

        wattroff(items_draw, COLOR_PAIR(3));

        // 增加y坐标以绘制下一个道具
        start_y += 7; // 根据字符画的高度调整
    }

    // 刷新窗口
    wrefresh(items_draw);
}

string get_item_description(string item) {
    // 根据道具名称返回对应的描述
    if (item == "handcuff") {
        return "restrain the dealer for one round";
    } else if (item == "cigarette") {
        return "gain an extra heart";
    } else if (item == "knife") {
        return "double the next bullet damage";
    } else if (item == "magnifyingGlass") {
        return "check current bullet";
    } else if (item == "beer") {
        return "eject current shell";
    } else if (item == "adrenaline") {
        return "steal an item from the dealer";
    } else {
        return "unknown item";
    }
}
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
