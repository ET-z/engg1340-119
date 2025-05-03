#ifndef SHELL_H
#define SHELL_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <curses.h>

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
    ShellGenerator(int t = 9, int mn = 3, int mx = 6) 
        : total(t), minLive(mn), maxLive(mx) {
        srand(time(0));
        validateParams();
        generate();
    }

    string getShells(){
	    string shellord = "";
	    for (int i = 0; i < total; ++i){
	    	shellord += to_string(shells[i]);
	    }
	    return shellord;
    }
};
#endif // SHELLGENERATOR_H
