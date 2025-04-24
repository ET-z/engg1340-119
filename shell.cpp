#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <memory>
#include <numeric>
#include <curses.h>

using namespace std;

// Shell container interface to define basic shell container behavior
class IShellContainer {
public:
    virtual ~IShellContainer() = default;
    virtual void validate() const = 0;
};

// Shell configuration class to store total shells, minimum live shells, and maximum live shells
class ShellConfig {
private:
    int total;    // Total number of shells
    int minLive;  // Minimum number of live shells
    int maxLive;  // Maximum number of live shells

public:
    ShellConfig(int t, int minL, int maxL) : total(t), minLive(minL), maxLive(maxL) {}

    int getTotal() const { return total; }
    int getMinLive() const { return minLive; }
    int getMaxLive() const { return maxLive; }
};

// Shell validator class to check if parameters are within valid ranges
class ShellValidator {
public:
    static void validateRange(int value, int min, int max, const string& name) {
        if (value < min || value > max) {
            stringstream ss;
            ss << name << " value " << value << " is out of range [" << min << "," << max << "]";
            throw runtime_error(ss.str());
        }
    }
};

// Shell generator class to create a list of randomly arranged shells
class ShellGenerator : public IShellContainer {
private:
    vector<int> shells;      // Vector to store shell states (0 for blank, 1 for live)
    int liveCount;          // Number of live shells
    int blankCount;         // Number of blank shells
    int totalShells;        // Total number of shells
    shared_ptr<ShellConfig> config;  // Shell configuration

    static int instanceCount;  // Static variable to track instance count
    const int instanceId;      // Unique identifier for the current instance

public:
    // Constructor to initialize the shell generator
    ShellGenerator(int total, int minLive, int maxLive)
        : totalShells(total), instanceId(++instanceCount) {
        // Initialize configuration
        initializeConfig(total, minLive, maxLive);
        // Initialize random seed
        initializeRandomSeed();
        // Validate initial parameters
        validateInitialParameters();
        // Calculate shell counts
        calculateShellCounts();
        // Generate shells
        generateShells();
    }

    // Initialize configuration
    void initializeConfig(int total, int minLive, int maxLive) {
        config = make_shared<ShellConfig>(total, minLive, maxLive);
    }

    // Initialize random seed
    void initializeRandomSeed() {
        srand(static_cast<unsigned int>(time(0)));
    }

    // Validate initial parameters are within valid ranges
    void validateInitialParameters() {
        ShellValidator::validateRange(config->getMinLive(), 0, config->getTotal(), "minLive");
        ShellValidator::validateRange(config->getMaxLive(), 0, config->getTotal(), "maxLive");

        if (config->getMinLive() > config->getMaxLive()) {
            throw runtime_error("minLive cannot be greater than maxLive");
        }
    }

    // Calculate the number of live and blank shells
    void calculateShellCounts() {
        int range = config->getMaxLive() - config->getMinLive();
        int randomOffset = rand() % (range + 1);
        liveCount = config->getMinLive() + randomOffset;
        blankCount = config->getTotal() - liveCount;
    }

    // Generate the list of shells
    void generateShells() {
        shells.clear();
        createPositionIndexes();
        performInitialShuffle();
        populateLiveShells();
        populateBlankShells();
        performFinalShuffle();
        validate();
    }

    // Create position indexes (not used, reserved for extension)
    void createPositionIndexes() {
        vector<int> positions(config->getTotal());
        iota(positions.begin(), positions.end(), 0);
    }

    // Initial shuffle (not used, reserved for extension)
    void performInitialShuffle() {
        vector<int> positions(config->getTotal());
        iota(positions.begin(), positions.end(), 0);
        random_shuffle(positions.begin(), positions.end());
    }

    // Populate live shells
    void populateLiveShells() {
        for (int i = 0; i < liveCount; ++i) {
            shells.push_back(1);
        }
    }

    // Populate blank shells
    void populateBlankShells() {
        for (int i = liveCount; i < config->getTotal(); ++i) {
            shells.push_back(0);
        }
    }

    // Final shuffle
    void performFinalShuffle() {
        random_shuffle(shells.begin(), shells.end());
    }

    // Validate the validity of the shell list
    void validate() const override {
        int actualLive = count(shells.begin(), shells.end(), 1);
        int actualBlank = count(shells.begin(), shells.end(), 0);

        if (actualLive != liveCount || actualBlank != blankCount) {
            throw runtime_error("Shell count validation failed");
        }

        if (shells.size() != config->getTotal()) {
            throw runtime_error("Total shells validation failed");
        }
    }

    // Get the list of shells
    vector<int> getShells() const {
        validate();
        return shells;
    }

    // Get the number of live shells
    int getLiveCount() const {
        validate();
        return liveCount;
    }

    // Get the number of blank shells
    int getBlankCount() const {
        validate();
        return blankCount;
    }

    // Reshuffle
    void reshuffle() {
        performFinalShuffle();
    }

    // Add a shell
    void addShell(int type) {
        if (type != 0 && type != 1) {
            throw invalid_argument("Invalid shell type");
        }

        if (type == 1) {
            liveCount++;
        } else {
            blankCount++;
        }

        shells.push_back(type);
        totalShells++;
        validate();
    }

    // Remove a shell
    void removeShell(int index) {
        if (index < 0 || index >= totalShells) {
            throw out_of_range("Invalid shell index");
        }

        int type = shells[index];
        if (type == 1) {
            liveCount--;
        } else {
            blankCount--;
        }

        shells.erase(shells.begin() + index);
        totalShells--;
        validate();
    }

    // Display statistics
    void displayStatistics() const {
        mvprintw(0, 0, "Shell Statistics:");
        mvprintw(1, 0, "Total shells: %d", totalShells);
        mvprintw(2, 0, "Live shells: %d", liveCount);
        mvprintw(3, 0, "Blank shells: %d", blankCount);
    }

    // Get instance ID
    int getInstanceId() const {
        return instanceId;
    }
};

// Initialize instance counter
int ShellGenerator::instanceCount = 0;

// Shell generator factory class to create default shell generators
class ShellGeneratorFactory {
public:
    static unique_ptr<ShellGenerator> createDefaultGenerator() {
        // Preset initial conditions: total shells 9, minimum live shells 1, maximum live shells 5
        return unique_ptr<ShellGenerator>(new ShellGenerator(9, 1, 5));
    }
};

// Function to generate shells
vector<int> generateShells() {
    auto generator = ShellGeneratorFactory::createDefaultGenerator();
    generator->displayStatistics();
    return generator->getShells();
}

// Function to get game shells
vector<int> getGameShells() {
    return generateShells();
}

// Main function
int main() {
    // Initialize Curses library
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Create default shell generator
    auto generator = ShellGeneratorFactory::createDefaultGenerator();

    // Display statistics
    generator->displayStatistics();

    // Get shells
    vector<int> shells = generator->getShells();

    // Display shell arrangement
    mvprintw(5, 0, "Shell arrangement: ");
    for (int i = 0; i < shells.size(); ++i) {
        mvprintw(6, i * 3, "%d", shells[i]);
    }

    // Refresh screen
    refresh();

    // Wait for user input
    getch();

    // Exit Curses library
    endwin();

    return 0;
}
