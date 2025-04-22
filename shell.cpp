#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class ShellGenerator {
private:
    vector<int> shells; //current situation for shells
    int liveCount; // num of live shell
    int blankCount; // numb of blank shell
    int totalShells; // num of total

public:
    ShellGenerator(int total, int minLive, int maxLive) : totalShells(total) {
        // initialize random seed
        srand(static_cast<unsigned int>(time(0)));

        // ensure num of live shell and blank shell within proper range
        if (minLive < 0) minLive = 0;
        if (maxLive > totalShells) maxLive = totalShells;
        if (minLive > maxLive) minLive = maxLive;

        // random num of live shell
        liveCount = rand() % (maxLive - minLive + 1) + minLive;
        blankCount = totalShells - liveCount;

        // generate shell
        generateShells();
    }

    void generateShells() {
        shells.clear();

        // create list
        vector<int> positions(totalShells);
        for (int i = 0; i < totalShells; ++i) {
            positions[i] = i;
        }

        // random
        random_shuffle(positions.begin(), positions.end());

        // Place live ammunition
        for (int i = 0; i < liveCount; ++i) {
            shells.push_back(1); 
        }

        // l the empty package
        for (int i = liveCount; i < totalShells; ++i) {
            shells.push_back(0);
        }

        // Shuffle again
        random_shuffle(shells.begin(), shells.end());
    }

    vector<int> getShells() const {
        return shells;
    }

    int getLiveCount() const {
        return liveCount;
    }

    int getBlankCount() const {
        return blankCount;
    }

    void reshuffle() {
        // Reshuffle the cartridge cases
        random_shuffle(shells.begin(), shells.end());
        cout << "Shells reshuffled." << endl;
    }

    void addShell(int type) {
        // Add a cartridge case (0 or 1)
        if (type == 1) {
            liveCount++;
        } else {
            blankCount++;
        }
        shells.push_back(type);
        totalShells++;
    }

    void removeShell(int index) {
        // Remove the cartridge case of the specified index
        if (index >= 0 && index < totalShells) {
            if (shells[index] == 1) {
                liveCount--;
            } else {
                blankCount--;
            }
            shells.erase(shells.begin() + index);
            totalShells--;
        }
    }

    void displayStatistics() const {
        // show the informstion
        cout << "Shell Statistics:" << endl;
        cout << "Total shells: " << totalShells << endl;
        cout << "Live shells: " << liveCount << endl;
        cout << "Blank shells: " << blankCount << endl;
    }
};

// Global function: Generate the cartridge case and return
vector<int> generateShells() {
    // a total of 9 bullets, with a minimum of 1 live bullet and a maximum of 5 live bullets
    ShellGenerator generator(9, 1, 5);

    // get list
    return generator.getShells();
}

// Call this function in the main loop
vector<int> getGameShells() {
    return generateShells();
}

