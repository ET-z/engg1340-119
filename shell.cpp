#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class ShellGenerator {
private:
    vector<int> shells; // 用于存储弹壳状态，1表示实弹，0表示空包
    int liveCount; // 实弹数量
    int blankCount; // 空包数量
    int totalShells; // 总弹壳数量

public:
    ShellGenerator(int total, int minLive, int maxLive) : totalShells(total) {
        // 初始化随机种子
        srand(static_cast<unsigned int>(time(0)));

        // 确保最小和最大实弹数量合理
        if (minLive < 0) minLive = 0;
        if (maxLive > totalShells) maxLive = totalShells;
        if (minLive > maxLive) minLive = maxLive;

        // 随机生成实弹数量（在指定范围内）
        liveCount = rand() % (maxLive - minLive + 1) + minLive;
        blankCount = totalShells - liveCount;

        // 生成弹壳序列
        generateShells();
    }

    void generateShells() {
        shells.clear();

        // 创建一个包含所有弹壳位置的列表
        vector<int> positions(totalShells);
        for (int i = 0; i < totalShells; ++i) {
            positions[i] = i;
        }

        // 随机打乱位置
        random_shuffle(positions.begin(), positions.end());

        // 在随机位置放置实弹
        for (int i = 0; i < liveCount; ++i) {
            shells.push_back(1); // 实弹
        }

        // 剩余位置填充空包
        for (int i = liveCount; i < totalShells; ++i) {
            shells.push_back(0); // 空包
        }

        // 再次打乱整个弹壳序列
        random_shuffle(shells.begin(), shells.end());

        // 输出生成的弹壳序列（用于调试）
        cout << "Generated shells: ";
        for (int shell : shells) {
            cout << shell << " ";
        }
        cout << endl;
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
        // 重新洗牌弹壳
        random_shuffle(shells.begin(), shells.end());
        cout << "Shells reshuffled." << endl;
    }

    void addShell(int type) {
        // 添加一个弹壳（0或1）
        if (type == 1) {
            liveCount++;
        } else {
            blankCount++;
        }
        shells.push_back(type);
        totalShells++;
    }

    void removeShell(int index) {
        // 移除指定索引的弹壳
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
        // 显示弹壳统计信息
        cout << "Shell Statistics:" << endl;
        cout << "Total shells: " << totalShells << endl;
        cout << "Live shells: " << liveCount << endl;
        cout << "Blank shells: " << blankCount << endl;
        cout << "Live percentage: " << (static_cast<double>(liveCount) / totalShells) * 100 << "%" << endl;
    }
};

// 全局函数：生成弹壳并返回
vector<int> generateShells() {
    // 创建弹壳生成器，总共有9发子弹，最少1发实弹，最多5发实弹
    ShellGenerator generator(9, 1, 5);

    // 获取生成的弹壳序列
    return generator.getShells();
}

// 测试函数
void testShellGenerator() {
    ShellGenerator generator(9, 1, 5);

    // 显示初始弹壳
    cout << "Initial shells: ";
    for (int shell : generator.getShells()) {
        cout << shell << " ";
    }
    cout << endl;

    // 显示统计信息
    generator.displayStatistics();

    // 重新洗牌
    generator.reshuffle();

    // 添加一个实弹
    generator.addShell(1);

    // 移除第一个弹壳
    generator.removeShell(0);

    // 显示更新后的统计信息
    generator.displayStatistics();
}

// 在游戏主循环中调用此函数来获取弹壳
vector<int> getGameShells() {
    return generateShells();
}

