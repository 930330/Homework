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
