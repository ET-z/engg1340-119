#include<iostream>
#include<vector>
#include<random>
using namespace std;
//create a shell with 9 shell packages
//and there should be at least 3 live shells and at most 6

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
//randomly generate shell
int sumShells(const std::vector<int>& shells) {
    int sum = 0;
    for (int shell : shells) {
        sum += shell;
    }
    return sum;
}
//sum the shells for checking 
int main() {
    vector<int> shells = generateShells(9);
    // make sure the shell number is between 3 and 6, and randomly generate it 
    while(sumShells(shells)<3||sumShells(shells)>6){
        shells = generateShells(9);
        return 0;
    }
}
