#ifndef SHELLS_H
#define SHELLS_H

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
    ShellGenerator(int total, int minLive, int maxLive);

    // Initialize configuration object
    void initializeConfig(int total, int minLive, int maxLive);

    // Seed random number generator
    void initializeRandomSeed();

    // Validate configuration parameters
    void validateInitialParameters();

    // Calculate live/blank shell counts
    void calculateShellCounts();

    // Main generation workflow
    void generateShells();

    // Create position indexes (reserved for future use)
    void createPositionIndexes();

    // Initial shuffle of positions (reserved for future use)
    void performInitialShuffle();

    // Add live shells to the collection
    void populateLiveShells();

    // Add blank shells to the collection
    void populateBlankShells();

    // Final shuffle of shells
    void performFinalShuffle();

    // Validate shell counts and totals
    void validate() const override;

    // Get shell collection
    vector<int> getShells() const;

    // Get live shell count
    int getLiveCount() const;

    // Get blank shell count
    int getBlankCount() const;

    // Get total shells from config
    int getTotalShells() const;

    // Re-shuffle existing shells
    void reshuffle();

    // Add new shell to collection
    void addShell(int type);

    // Remove shell from collection
    void removeShell(int index);

    // Display centered information using ncurses
    void displayCentered(int max_y, int max_x) const;

    // Get instance identifier
    int getInstanceId() const;
};

// Factory class for creating generators
class ShellGeneratorFactory {
public:
    // Create generator with default configuration
    static unique_ptr<ShellGenerator> createDefaultGenerator();
};

#endif // SHELLS_H
