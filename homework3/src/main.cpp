#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;
using namespace std::chrono;

struct TermNode {
    int coef;
    int exp;
    TermNode* link;
};

class Polynomial {
private:
    TermNode* head;

    void clear() {
        TermNode* cur = head->link;
        while (cur != head) {
            TermNode* temp = cur;
            cur = cur->link;
            delete temp;
        }
        head->link = head;
    }

public:
    Polynomial() {
        head = new TermNode;
        head->link = head;
    }

    Polynomial(const Polynomial& other) : Polynomial() {
        TermNode* cur = other.head->link;
        while (cur != other.head) {
            insertTerm(cur->coef, cur->exp);
            cur = cur->link;
        }
    }

    ~Polynomial() {
        clear();
        delete head;
    }

    // 插入並合併同指數項
    void insertTerm(int c, int e) {
        if (c == 0) return;
        TermNode* cur = head;
        while (cur->link != head && cur->link->exp > e) cur = cur->link;

        // 如果存在相同指數，合併
        if (cur->link != head && cur->link->exp == e) {
            cur->link->coef += c;
            if (cur->link->coef == 0) { // 刪除 0 項
                TermNode* temp = cur->link;
                cur->link = temp->link;
                delete temp;
            }
            return;
        }

        // 插入新節點
        TermNode* newNode = new TermNode{c, e, cur->link};
        cur->link = newNode;
    }

    // 解析多項式字串
    void parsePolynomial(string input) {
        clear();
        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
        if (input.empty()) return;

        if (input[0] != '-' && input[0] != '+') input = "+" + input;

        for (size_t i = 0; i < input.size();) {
            int sign = 1;
            if (input[i] == '+') { sign = 1; i++; }
            else if (input[i] == '-') { sign = -1; i++; }

            int coef = 0, exp = 0;
            bool hasX = false;

            // 讀取係數
            while (i < input.size() && isdigit(input[i])) {
                coef = coef * 10 + (input[i] - '0');
                i++;
            }
            if (coef == 0) coef = 1;
            coef *= sign;

            // 處理 x
            if (i < input.size() && input[i] == 'x') {
                hasX = true;
                i++;
                exp = 1;
                if (i < input.size() && input[i] == '^') {
                    i++;
                    exp = 0;
                    while (i < input.size() && isdigit(input[i])) {
                        exp = exp * 10 + (input[i]-'0');
                        i++;
                    }
                }
            } else {
                exp = 0; // 常數項
            }

            insertTerm(coef, exp);
        }
    }

    string toString() const {
        TermNode* cur = head->link;
        if (cur == head) return "0";

        ostringstream os;
        bool first = true;
        while (cur != head) {
            int c = cur->coef, e = cur->exp;
            if (!first) os << (c > 0 ? "+" : "");
            if (e == 0) os << c;
            else if (e == 1) {
                if (c == 1) os << "x";
                else if (c == -1) os << "-x";
                else os << c << "x";
            } else {
                if (c == 1) os << "x^" << e;
                else if (c == -1) os << "-x^" << e;
                else os << c << "x^" << e;
            }
            first = false;
            cur = cur->link;
        }
        return os.str();
    }

    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        TermNode* p = head->link;
        TermNode* q = b.head->link;
        while (p != head && q != b.head) {
            if (p->exp == q->exp) {
                int sumCoef = p->coef + q->coef;
                if (sumCoef != 0) result.insertTerm(sumCoef, p->exp);
                p = p->link;
                q = q->link;
            } else if (p->exp > q->exp) {
                result.insertTerm(p->coef, p->exp);
                p = p->link;
            } else {
                result.insertTerm(q->coef, q->exp);
                q = q->link;
            }
        }
        while (p != head) { result.insertTerm(p->coef, p->exp); p = p->link; }
        while (q != b.head) { result.insertTerm(q->coef, q->exp); q = q->link; }
        return result;
    }

    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        TermNode* p = head->link;
        TermNode* q = b.head->link;
        while (p != head && q != b.head) {
            if (p->exp == q->exp) {
                int diffCoef = p->coef - q->coef;
                if (diffCoef != 0) result.insertTerm(diffCoef, p->exp);
                p = p->link;
                q = q->link;
            } else if (p->exp > q->exp) {
                result.insertTerm(p->coef, p->exp);
                p = p->link;
            } else {
                result.insertTerm(-q->coef, q->exp);
                q = q->link;
            }
        }
        while (p != head) { result.insertTerm(p->coef, p->exp); p = p->link; }
        while (q != b.head) { result.insertTerm(-q->coef, q->exp); q = q->link; }
        return result;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        for (TermNode* p = head->link; p != head; p = p->link) {
            for (TermNode* q = b.head->link; q != b.head; q = q->link) {
                result.insertTerm(p->coef * q->coef, p->exp + q->exp);
            }
        }
        return result;
    }

    double Evaluate(double x) const {
        double result = 0;
        TermNode* cur = head->link;
        while (cur != head) {
            result += static_cast<double>(cur->coef) * pow(x, cur->exp);
            cur = cur->link;
        }
        return result;
    }
};

int main() {
    Polynomial a, b;
    cout << "輸入a多項式：";
    string sa; cin >> sa;
    a.parsePolynomial(sa);

    cout << "輸入b多項式：";
    string sb; cin >> sb;
    b.parsePolynomial(sb);

    cout << "-------------------------" << endl;
    cout << "a = " << a.toString() << endl;
    cout << "b = " << b.toString() << endl;

    auto start = high_resolution_clock::now();
    Polynomial sum = a + b;
    auto end = high_resolution_clock::now();
    cout << "a + b = " << sum.toString()
         << "  需時：" 
         << duration_cast<microseconds>(end-start).count()/1000.0 << "s\n";

    start = high_resolution_clock::now();
    Polynomial diff = a - b;
    end = high_resolution_clock::now();
    cout << "a - b = " << diff.toString()
         << "  需時：" 
         << duration_cast<microseconds>(end-start).count()/1000.0 << "s\n";

    start = high_resolution_clock::now();
    Polynomial prod = a * b;
    end = high_resolution_clock::now();
    cout << "a * b = " << prod.toString()
         << "  需時：" 
         << duration_cast<microseconds>(end-start).count()/1000.0 << "s\n";

    cout << "-------------------------" << endl;
    cout << "請輸入x，以求出a(x)、b(x)的值?";
    double x; cin >> x;

    start = high_resolution_clock::now();
    double va = a.Evaluate(x);
    end = high_resolution_clock::now();
    cout << left << setw(8) << "a(x) = " << setw(8) << va
         << "需時：" << duration_cast<microseconds>(end-start).count()/1000.0 << "s\n";

    start = high_resolution_clock::now();
    double vb = b.Evaluate(x);
    end = high_resolution_clock::now();
    cout << left << setw(8) << "b(x) = " << setw(8) << vb
         << "需時：" << duration_cast<microseconds>(end-start).count()/1000.0 << "s\n";

    return 0;
}
```cpp
## 效能分析
加法：時間複雜度 O(m+n)，空間複雜度 O(m+n)

乘法：時間複雜度 O(m×n)，空間複雜度 O(m×n)

求值：時間複雜度 O(n)，僅需遍歷一次多項式項目

## 測試與驗證
| 測試編號 | 輸入多項式 1      | 輸入多項式 2 | 測試項目 | 結果           |
| ---- | ------------ | ------- | ---- | ------------ |
| 測試 1 | 3x² + 2x + 1 | x² + 4  | 加法   | 4x² + 2x + 5 |
| 測試 2 | 2x + 3       | x + 1   | 乘法   | 2x² + 5x + 3 |
| 測試 3 | x² + 2x + 1  | x = 2   | 求值   | 9            |

### 編譯與執行指令
```cpp
g++ -std=c++17 -o polynomial polynomial.cpp
./polynomial
```cpp
##結論
成功實作 Polynomial 類別，支援加法、乘法與求值。

記憶體使用動態配置，程式結構簡潔且容易維護。

透過友元函式讓 I/O 操作直觀，符合物件導向設計理念。

##申論及開發報告
1.數學與程式設計對應

多項式結構天然對應物件導向概念，項目封裝於 Term 類別。

2.演算法設計簡單明瞭

加法與乘法依指數大小排序處理，符合數學規則。

3.動態記憶體運用彈性

依輸入項數配置記憶體，避免浪費，並確保解構子釋放資源。

4.模組化與擴充性佳

可輕鬆擴充微分、排序或化簡等功能。




