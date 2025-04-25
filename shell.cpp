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

// Interface for shell containers
class IShellContainer {
public:
    virtual ~IShellContainer() = default;
    virtual void validate() const = 0;  // Validation interface
};

// Configuration class for shell parameters
class ShellConfig {
private:
    int total;     // Total number of shells
    int minLive;   // Minimum live shells
    int maxLive;   // Maximum live shells

public:
    ShellConfig(int t, int minL, int maxL) : total(t), minLive(minL), maxLive(maxL) {}

    // Accessors
    int getTotal() const { return total; }
    int getMinLive() const { return minLive; }
    int getMaxLive() const { return maxLive; }
};

// Validation utility class
class ShellValidator {
public:
    // Validate value range with error message
    static void validateRange(int value, int min, int max, const string& name) {
        if (value < min || value > max) {
            stringstream ss;
            ss << name << " value " << value << " is out of range [" << min << "," << max << "]";
            throw runtime_error(ss.str());
        }
    }
};

// Main shell generator class
class ShellGenerator : public IShellContainer {
private:
    vector<int> shells;       // 1=live, 0=blank shells
    int liveCount;            // Current live shell count
    int blankCount;           // Current blank shell count
    int totalShells;          // Total shells (cached value)
    shared_ptr<ShellConfig> config;  // Configuration reference

    static int instanceCount; // Class-level instance counter
    const int instanceId;     // Unique instance ID

public:
    // Constructor with parameter validation
    ShellGenerator(int total, int minLive, int maxLive)
        : totalShells(total), instanceId(++instanceCount) {
        initializeConfig(total, minLive, maxLive);
        initializeRandomSeed();
        validateInitialParameters();
        calculateShellCounts();
        generateShells();
    }

    // Initialize configuration object
    void initializeConfig(int total, int minLive, int maxLive) {
        config = make_shared<ShellConfig>(total, minLive, maxLive);
    }

    // Seed random number generator
    void initializeRandomSeed() {
        srand(static_cast<unsigned int>(time(0)));
    }

    // Validate configuration parameters
    void validateInitialParameters() {
        ShellValidator::validateRange(config->getMinLive(), 0, config->getTotal(), "minLive");
        ShellValidator::validateRange(config->getMaxLive(), 0, config->getTotal(), "maxLive");

        if (config->getMinLive() > config->getMaxLive()) {
            throw runtime_error("minLive cannot be greater than maxLive");
        }
    }

    // Calculate live/blank shell counts
    void calculateShellCounts() {
        int range = config->getMaxLive() - config->getMinLive();
        int randomOffset = rand() % (range + 1);
        liveCount = config->getMinLive() + randomOffset;
        blankCount = config->getTotal() - liveCount;
    }

    // Main generation workflow
    void generateShells() {
        shells.clear();
        createPositionIndexes();
        performInitialShuffle();
        populateLiveShells();
        populateBlankShells();
        performFinalShuffle();
        validate();
    }

    // Create position indexes (reserved for future use)
    void createPositionIndexes() {
        vector<int> positions(config->getTotal());
        iota(positions.begin(), positions.end(), 0);
    }

    // Initial shuffle of positions (reserved for future use)
    void performInitialShuffle() {
        vector<int> positions(config->getTotal());
        iota(positions.begin(), positions.end(), 0);
        random_shuffle(positions.begin(), positions.end());
    }

    // Add live shells to the collection
    void populateLiveShells() {
        for (int i = 0; i < liveCount; ++i) {
            shells.push_back(1);
        }
    }

    // Add blank shells to the collection
    void populateBlankShells() {
        for (int i = liveCount; i < config->getTotal(); ++i) {
            shells.push_back(0);
        }
    }

    // Final shuffle of shells
    void performFinalShuffle() {
        random_shuffle(shells.begin(), shells.end());
    }

    // Validate shell counts and totals
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

    // Get shell collection
    vector<int> getShells() const {
        validate();
        return shells;
    }

    // Get live shell count
    int getLiveCount() const {
        validate();
        return liveCount;
    }

    // Get blank shell count
    int getBlankCount() const {
        validate();
        return blankCount;
    }

    // Get total shells from config
    int getTotalShells() const {
        return config->getTotal();
    }

    // Re-shuffle existing shells
    void reshuffle() {
        performFinalShuffle();
    }

    // Add new shell to collection
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

    // Remove shell from collection
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

    // Display centered information using ncurses
    void displayCentered(int max_y, int max_x) const {
        // Prepare display content
        vector<string> content = {
            "Shell Statistics:",
            "Total shells: " + to_string(getTotalShells()),
            "Live shells: " + to_string(getLiveCount()),
            "Blank shells: " + to_string(getBlankCount()),
            "", // Empty line
            "Shell arrangement: "
        };

        // Convert shell array to string
        string shells_str;
        for (int s : shells) {
            shells_str += to_string(s) + " ";
        }
        content.push_back(shells_str);
        content.push_back(""); // Empty line
        content.push_back("Press any key to exit...");

        // Calculate vertical start position
        int start_y = (max_y - content.size()) / 2;

        // Clear screen and print centered content
        clear();
        for (size_t i = 0; i < content.size(); ++i) {
            // Calculate horizontal position
            int x = (max_x - content[i].length()) / 2;
            // Prevent negative x values
            x = x < 0 ? 0 : x; 
            // Print centered line
            mvprintw(start_y + i, x, "%s", content[i].c_str());
        }
        refresh();
    }

    // Get instance identifier
    int getInstanceId() const {
        return instanceId;
    }
};

// Initialize static instance counter
int ShellGenerator::instanceCount = 0;

// Factory class for creating generators
class ShellGeneratorFactory {
public:
    // Create generator with default configuration
    static unique_ptr<ShellGenerator> createDefaultGenerator() {
        return unique_ptr<ShellGenerator>(new ShellGenerator(9, 1, 5));
    }
};
