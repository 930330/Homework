# 41141114
## 作業一
## 解題說明
本題要求實作一個 Polynomial 類別，其抽象資料型態（ADT）和私有成員，能對多項式進行下列操作
## 解題策略
1.根據 ADT 建立類別 Polynomial，並實作：

建構子

多項式加法 Add

多項式乘法 Mult

多項式求值 Eval

2.定義私有內部類別 Term，儲存每一項的係數與指數。

3.使用動態陣列 termArray 儲存多項式項數，並維護其大小與容量。

4.實作 >> 與 << 運算子以便於輸入與輸出。

5.處理邊界情況，如項數為 0、多項式相加合併指數相同的項等。
## 程式實作
```cpp
#include <iostream>
#include <cmath>  // for pow
using namespace std;

// Term 類別
class Term {
private:
    float coef;  // 係數
    int exp;     // 指數

public:
    // Getter
    float getCoef() const { return coef; }
    int getExp() const { return exp; }

    // Setter
    void setCoef(float c) { coef = c; }
    void setExp(int e) { exp = e; }
};

// Polynomial 類別
class Polynomial {
public:
    Polynomial();                     // 建構子
    ~Polynomial();                    // 解構子
    Polynomial Add(const Polynomial& poly);  // 多項式加法
    Polynomial Mult(const Polynomial& poly); // 多項式乘法
    float Eval(float f);             // 多項式求值

    friend ostream& operator<<(ostream& out, const Polynomial& poly);
    friend istream& operator>>(istream& in, Polynomial& poly);

private:
    Term* termArray; // 非零項陣列
    int capacity;    // 陣列大小
    int terms;       // 非零項個數
};

// 建構子
Polynomial::Polynomial() {
    capacity = 10;
    terms = 0;
    termArray = new Term[capacity];
}

// 解構子
Polynomial::~Polynomial() {
    delete[] termArray;
}

// 輸入運算子 >>
istream& operator>>(istream& in, Polynomial& poly) {
    cout << "Enter number of terms: ";
    in >> poly.terms;
    poly.capacity = poly.terms;
    delete[] poly.termArray;
    poly.termArray = new Term[poly.capacity];

    for (int i = 0; i < poly.terms; i++) {
        float c;
        int e;
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        in >> c >> e;
        poly.termArray[i].setCoef(c);
        poly.termArray[i].setExp(e);
    }
    return in;
}

// 輸出運算子 <<
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; i++) {
        out << poly.termArray[i].getCoef() << "x^" << poly.termArray[i].getExp();
        if (i != poly.terms - 1)
            out << " + ";
    }
    return out;
}

// 多項式加法
Polynomial Polynomial::Add(const Polynomial& poly) {
    Polynomial result;
    result.capacity = terms + poly.terms;
    result.termArray = new Term[result.capacity];
    int i = 0, j = 0, k = 0;

    while (i < terms && j < poly.terms) {
        int exp1 = termArray[i].getExp();
        int exp2 = poly.termArray[j].getExp();

        if (exp1 == exp2) {
            float sum = termArray[i].getCoef() + poly.termArray[j].getCoef();
            if (sum != 0) {
                result.termArray[k].setCoef(sum);
                result.termArray[k].setExp(exp1);
                k++;
            }
            i++; j++;
        } else if (exp1 > exp2) {
            result.termArray[k] = termArray[i];
            i++; k++;
        } else {
            result.termArray[k] = poly.termArray[j];
            j++; k++;
        }
    }

    while (i < terms) result.termArray[k++] = termArray[i++];
    while (j < poly.terms) result.termArray[k++] = poly.termArray[j++];

    result.terms = k;
    return result;
}

// 多項式乘法
Polynomial Polynomial::Mult(const Polynomial& poly) {
    Polynomial result;
    result.capacity = terms * poly.terms;
    result.termArray = new Term[result.capacity];
    result.terms = 0;

    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < poly.terms; j++) {
            float c = termArray[i].getCoef() * poly.termArray[j].getCoef();
            int e = termArray[i].getExp() + poly.termArray[j].getExp();

            bool found = false;
            for (int k = 0; k < result.terms; k++) {
                if (result.termArray[k].getExp() == e) {
                    float updatedCoef = result.termArray[k].getCoef() + c;
                    result.termArray[k].setCoef(updatedCoef);
                    found = true;
                    break;
                }
            }

            if (!found) {
                result.termArray[result.terms].setCoef(c);
                result.termArray[result.terms].setExp(e);
                result.terms++;
            }
        }
    }

    return result;
}

// 多項式求值
float Polynomial::Eval(float f) {
    float result = 0;
    for (int i = 0; i < terms; i++) {
        result += termArray[i].getCoef() * pow(f, termArray[i].getExp());
    }
    return result;
}

// 主程式
int main() {
    Polynomial p1, p2;

    cout << "Input Polynomial 1:\n";
    cin >> p1;

    cout << "\nInput Polynomial 2:\n";
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "\nPolynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;
    cout << "Sum: " << sum << endl;
    cout << "Product: " << product << endl;

    float x;
    cout << "\nEnter a value to evaluate Polynomial 1: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Eval(x) << endl;

    return 0;
}
```
## 效能分析
時間複雜度

加法：O(m + n)，其中 m 與 n 為兩個多項式的項數

乘法：O(m × n)

求值：O(n)，需要依序計算每項

空間複雜度

動態陣列為主，最多為 m×n 項儲存乘積結果

## 測試與驗證
| 測試編號 | 輸入多項式 1      | 輸入多項式 2 | 測試項目 | 結果           |
| ---- | ------------ | ------- | ---- | ------------ |
| 測試 1 | 3x² + 2x + 1 | x² + 4  | 加法   | 4x² + 2x + 5 |
| 測試 2 | 2x + 3       | x + 1   | 乘法   | 2x² + 5x + 3 |
| 測試 3 | x² + 2x + 1  | x = 2   | 求值   | 9            |
### 編譯與執行指令
```
g++ -std=c++17 -o polynomial polynomial.cpp
./polynomial
```
## 結論
此程式實作一套完整的 Polynomial 類別，支援基本運算與求值操作。

加法與乘法考慮指數對應，可正確處理同類項合併

程式碼使用動態記憶體與陣列管理非零項，效率合理

透過友元函式實作輸入輸出，提升程式整體易用性

## 申論及開發報告
1.數學定義自然對應物件導向設計
多項式由數學上的一連串項（Term）所組成，每一項由「係數 + 指數」構成，極適合用類別（Class）結構來封裝與表達。

透過 Term 與 Polynomial 兩個類別，可清楚地對應多項式的邏輯結構，也方便進行擴充與管理。

2.邏輯清晰，運算對應數學規則
多項式的加法與乘法都根據指數大小進行處理，符合數學上同類項合併與乘法展開的概念。

加法時，對應相同次方的項目相加

乘法時，使用分配律展開後進行同類項合併

程式中運用簡單迴圈與條件判斷完成這些運算，結構清晰，邏輯明確。

3.程式簡潔，動態記憶體運用彈性
本程式使用動態陣列儲存非零項，根據實際輸入項數配置記憶體，避免空間浪費。

而且使用了 建構子 / 解構子 管理資源釋放，符合 C++ 面向物件開發原則，避免記憶體洩漏。

4.類別設計有助於模組化與可擴充性
使用 friend 函數支援直觀的輸入與輸出

各種操作（加法、乘法、求值）皆封裝在 Polynomial 類別中

將項（Term）獨立成類別後，未來可擴充其他功能如微分、排序、化簡等

5.效能良好，適用於中小型多項式
對於數項在 10~100 項範圍的多項式，加法與乘法效率足夠。
