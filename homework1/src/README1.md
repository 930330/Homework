## 41141114
作業一
## 解題說明
本題要求實現一個 遞迴函式，計算 Ackermann 函數𝐴(𝑚,𝑛)的值。
## 解題策略
1. 使用遞迴函式將問題拆解為更小的子問題

   ```cpp
   若 m=0，回傳 n+1
   若 n=0，回傳 A(m−1,1)
   否則，先計算 A(m,𝑛−1)，再以結果作為第二個參數，繼續計算 A(m−1,...)
   當 m=0 時，返回 n+1 作為遞迴的結束條件
3. 主程式呼叫遞迴函式，並輸出計算結果

## 程式實作
以下為主要程式碼：

```cpp
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
```
## 效能分析
時間複雜度：程式的時間複雜度為 O(A(m,n))。

Ackermann 函數的成長速度非常快，甚至比指數函數還快，其遞迴呼叫次數會隨著 m 和 n 急劇增加。對於輸入 m 和 n 的不同組合，其執行時間近乎呈現超指數級別成長

空間複雜度：空間複雜度為 O(A(m,n))。

程式每次遞迴呼叫都會佔用一次堆疊空間，最壞情況下的呼叫深度接近 Ackermann 函數本身的值，空間需求也會非常高。

## 測試與驗證
### Ackermann 函數測試案例
| 測試編號 | 輸入 (m, n) | 預期結果     | 實際結果               | 
|----------|--------------|--------------|------------------------|
| 測試 1   | (0, 0)       | 1            | 1                   |
| 測試 2   | (1, 2)       | 4            | 4                   |
| 測試 3   | (2, 2)       | 7            | 7                   |
| 測試 4   | (3, 3)       | 61           | 61                 |
| 測試 5   | (4, 1)       |  錯誤或崩潰 |  Stack overflow / 無法執行 |

### 編譯與執行指令
$ g++ -std=c++17 -o Ackermann main.cpp
$ ./Ackermann

## 結論
程式能正確計算 Ackermann 函數 A(m, n) 的結果。
在給定有效的 m 和 n（特別是 m ≦ 3）的情況下，能準確輸出對應值。
對於 m > 3 或 n 值過大，程式可能導致堆疊溢位（Stack Overflow），
但若加上參數限制與例外處理，可有效避免程式當機，符合設計預期。

測試案例涵蓋了多種邊界情況（m = 0、m = 1、m = 2、m = 3、m = 4），
成功驗證程式在合理輸入範圍內的正確性與穩定性。

## 申論及開發報告
### 選擇遞迴的原因
函數定義本身為遞迴形式
程式結構簡潔直觀
使用遞迴可以讓程式碼對應到數學公式的層次關係，提升可讀性與邏輯清晰度。
核心實作如下：
```cpp
int ackermann_recursive(int m, int n) {
    if (m == 0) return n + 1;
    else if (n == 0) return ackermann_recursive(m - 1, 1);
    else return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}
```
有助於理解遞迴深度與效能影響
Ackermann 函數是經典的「超快速增長」，透過遞迴實作可展示遞迴呼叫堆疊的深度變化，有助於學習遞迴對資源使用（如 Stack）之影響。

遞迴在表達 Ackermann 函數時極為直觀，其成長速度極快，當輸入過大時（例如 m ≥ 4），會造成 Stack Overflow 或效能問題。因此在實際應用中限制輸入範圍，來提升穩定性。
