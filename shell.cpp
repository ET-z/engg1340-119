//////// If this version is too complicated, I have a simple one. I can change it. Just let me know in the group thx！
// the throw, and cout should be changed into mvprintw
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <memory>
#include <numeric>

using namespace std;

class IShellContainer {
public:
    virtual ~IShellContainer() = default;
    virtual void validate() const = 0;
};

class ShellConfig {
private:
    int total;
    int minLive;
    int maxLive;

public:
    ShellConfig(int t, int minL, int maxL) : total(t), minLive(minL), maxLive(maxL) {}

    int getTotal() const { return total; }
    int getMinLive() const { return minLive; }
    int getMaxLive() const { return maxLive; }
};

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

class ShellGenerator : public IShellContainer {
private:
    vector<int> shells;
    int liveCount;
    int blankCount;
    int totalShells;
    shared_ptr<ShellConfig> config;

    static int instanceCount;
    const int instanceId;

public:
    ShellGenerator(int total, int minLive, int maxLive)
        : totalShells(total), instanceId(++instanceCount) {
        initializeConfig(total, minLive, maxLive);
        initializeRandomSeed();
        validateInitialParameters();
        calculateShellCounts();
        generateShells();
    }

    void initializeConfig(int total, int minLive, int maxLive) {
        config = make_shared<ShellConfig>(total, minLive, maxLive);
    }

    void initializeRandomSeed() {
        srand(static_cast<unsigned int>(time(0)));
    }

    void validateInitialParameters() {
        ShellValidator::validateRange(config->getMinLive(), 0, config->getTotal(), "minLive");
        ShellValidator::validateRange(config->getMaxLive(), 0, config->getTotal(), "maxLive");

        if (config->getMinLive() > config->getMaxLive()) {
            throw runtime_error("minLive cannot be greater than maxLive");
        }
    }

    void calculateShellCounts() {
        int range = config->getMaxLive() - config->getMinLive();
        int randomOffset = rand() % (range + 1);
        liveCount = config->getMinLive() + randomOffset;
        blankCount = config->getTotal() - liveCount;
    }

    void generateShells() {
        shells.clear();
        createPositionIndexes();
        performInitialShuffle();
        populateLiveShells();
        populateBlankShells();
        performFinalShuffle();
        validate();
    }

    void createPositionIndexes() {
        vector<int> positions(config->getTotal());
        iota(positions.begin(), positions.end(), 0);
    }

    void performInitialShuffle() {
        vector<int> positions(config->getTotal());
        iota(positions.begin(), positions.end(), 0);
        random_shuffle(positions.begin(), positions.end());
    }

    void populateLiveShells() {
        for (int i = 0; i < liveCount; ++i) {
            shells.push_back(1);
        }
    }

    void populateBlankShells() {
        for (int i = liveCount; i < config->getTotal(); ++i) {
            shells.push_back(0);
        }
    }

    void performFinalShuffle() {
        random_shuffle(shells.begin(), shells.end());
    }

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

    vector<int> getShells() const {
        validate();
        return shells;
    }

    int getLiveCount() const {
        validate();
        return liveCount;
    }

    int getBlankCount() const {
        validate();
        return blankCount;
    }

    void reshuffle() {
        performFinalShuffle();
    }

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

    void displayStatistics() const {
        cout << "Shell Statistics:" << endl;
        cout << "Total shells: " << totalShells << endl;
        cout << "Live shells: " << liveCount << endl;
        cout << "Blank shells: " << blankCount << endl;
    }

    int getInstanceId() const {
        return instanceId;
    }
};

int ShellGenerator::instanceCount = 0;

class ShellGeneratorFactory {
public:
    static unique_ptr<ShellGenerator> createDefaultGenerator() {
        return unique_ptr<ShellGenerator>(new ShellGenerator(9, 1, 5));
    }
};

vector<int> generateShells() {
    auto generator = ShellGeneratorFactory::createDefaultGenerator();
    generator->displayStatistics();
    return generator->getShells();
}

vector<int> getGameShells() {
    return generateShells();
}


///////// If this version is too complicated, I have a simple one. I can change it. Just let me know in the group thx！


int main() {       // The calling method in the main function
    auto generator = ShellGeneratorFactory::createDefaultGenerator();
    generator->displayStatistics(); 

    vector<int> shells = generator->getShells(); // Obtain the arrangement of the shells
    cout << "Shell arrangement: ";
    for (int shell : shells) {
        cout << shell << " ";// Print the status of each shell
    }
    cout << endl;

    return 0;
}
