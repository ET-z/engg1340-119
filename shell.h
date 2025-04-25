#ifndef SHELLGENERATOR_H
#define SHELLGENERATOR_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <exception>
#include <string>
#include <curses.h>

using namespace std;

class ShellGenerator {
private:
    vector<bool> shells;
    int total;
    int minLive;
    int maxLive;

    void validateParams();
    void generate();

public:
    ShellGenerator(int t = 9, int mn = 1, int mx = 5);
    void display();
};

#endif // SHELLGENERATOR_H
