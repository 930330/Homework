#include <iostream>
using namespace std;

// 遞迴實作 Ackermann 函數
int ackermann_recursive(int m, int n) {
    if (m == 0) return n + 1;
    else if (n == 0) return ackermann_recursive(m - 1, 1);
    else return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}

int main() {
    int m, n;
    cout << "請輸入 m ：";
    cin >> m;
    cout << "請輸入 n 的值：";
    cin >> n;

    // 安全限制（可調整）
    if (m > 3 || n > 10) {
        cout << "錯誤：m 或 n 太大，可能造成 Stack Overflow。請輸入較小的數值。" << endl;
        return 1;
    }

    try {
        int result = ackermann_recursive(m, n);
        cout << "Ackermann 函數結果為：" << result << endl;
    } catch (...) {
        cout << "發生例外：可能堆疊溢位。" << endl;
    }

    return 0;
}
