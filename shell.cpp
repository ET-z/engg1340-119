#include<iostream>
#include<vector>
#include<random>
using namespace std;
vector<int> generateShells(int size) {
    vector<int> shells(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 1);

    for (int i = 0; i < size; i++) {
        shells[i] = dis(gen);
    }
    return shells;
}
int sumShells(const std::vector<int>& shells) {
    int sum = 0;
    for (int shell : shells) {
        sum += shell;
    }
    return sum;
}
int main() {
    vector<int> shells = generateShells(9);
    while(sumShells(shells)<3){
        shells = generateShells(9);
    }
}
