#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <curses.h>
#include "shell.h"

using namespace std;

class ShellGenerator {
private:
    vector<bool> shells;
    int total;
    int minLive;
    int maxLive;

    void validateParams() {
        if (minLive < 0 || maxLive > total || minLive > maxLive)
            throw runtime_error("Invalid parameters");
    }

    void generate() {
        int live = minLive + rand() % (maxLive - minLive + 1);
        shells.resize(total);
        fill(shells.begin(), shells.begin() + live, true);
        fill(shells.begin() + live, shells.end(), false);
        random_shuffle(shells.begin(), shells.end());
    }

public:
    ShellGenerator(int t = 9, int mn = 1, int mx = 5) 
        : total(t), minLive(mn), maxLive(mx) {
        srand(time(0));
        validateParams();
        generate();
    }

    void display() {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        vector<string> content = {
            "Shell Game:",
            "Total: " + to_string(total),
            "Live: " + to_string(count(shells.begin(), shells.end(), true)),
            "Arrangement:"
        };
        
        string shells_str;
        for(bool s : shells) shells_str += s ? "1 " : "0 ";
        content.push_back(shells_str);
        
        clear();
        for(size_t i=0; i<content.size(); ++i) {
            int y = (max_y - content.size())/2 + i;
            int x = (max_x - content[i].size())/2;
            mvaddstr(y, x>0 ? x : 0, content[i].c_str());
        }
        refresh();
    }
};
   
    //ShellGenerator game;
    //game.display()
