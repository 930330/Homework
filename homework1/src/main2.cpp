#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 遞迴計算 Power Set
void generatePowerSet(const vector<char>& set, int index, string current) {
    if (index == set.size()) {
        cout << "{" << current << "}" << endl;
        return;
    }

    // 不選當前元素
    generatePowerSet(set, index + 1, current);

    // 選當前元素
    generatePowerSet(set, index + 1, current + set[index]);
}

int main() {
    vector<char> S = {'a', 'b', 'c'};
    cout << "Power set of {a, b, c}:\n";
    generatePowerSet(S, 0, "");
    return 0;
}
