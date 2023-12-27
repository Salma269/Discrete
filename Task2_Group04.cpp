#include <iostream>
using namespace std;

bool change;

bool originalExpression(bool A, bool B, bool C) {
    return ((A || B) && (A && B)) || (B && !B) || (C && B);
}

bool ModifiedExpression(bool A, bool B, bool C) {
    return ((A || B) && (A && B)) || (B && B) || (C && B);
}

bool simplifiedExpression(bool A, bool B, bool C) {
    return (A || C) && B;
}


void printTruthTable(bool change, bool A[],bool B[], bool C[] ) {
    if (!change) {
        cout << "A\tB\tC\t(A || B)\t(A & B)\t\t[(A || B) & (A & B)]\t(B & ~B)\t(C & B)\t\tOrig\t(A || C)\tSimp\n";
    }
    else {
        cout << "A\tB\tC\t(A || B)\t(A & B)\t\t[(A || B) & (A & B)]\t(B & B)\t\t(C & B)\t\tOrig\tSimp\n";
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                if (!change) {
                    bool original = originalExpression(A[i], B[j], C[k]);
                    bool simplified = simplifiedExpression(A[i], B[j], C[k]);
                    cout << A[i] << "\t" << B[j] << "\t" << C[k] << "\t" << (A[i] || B[j]) << "\t\t" << (A[i] && B[j]) << "\t\t\t" << ((A[i] || B[j]) && (A[i] && B[j])) << "\t\t" << (B[j] && !B[j]) << "\t\t" << (C[k] && B[j]) << "\t\t" << original << "\t" << (A[i] || C[k]) << "\t\t" << simplified << endl;
                    if (original != simplified) {
                        cout << "The two expressions are not equivalent." << endl;
                    }
                }
                else {
                    bool original = ModifiedExpression(A[i], B[j], C[k]);
                    bool simplified = B[j];
                    cout << A[i] << "\t" << B[j] << "\t" << C[k] << "\t" << (A[i] || B[j]) << "\t\t" << (A[i] && B[j]) << "\t\t\t" << ((A[i] || B[j]) && (A[i] && B[j])) << "\t\t" << (B[j] && B[j]) << "\t\t" << (C[k] && B[j]) << "\t\t" << original << "\t" << simplified << "\n";
                    if (original != simplified) {
                        cout << "The two expressions are not equivalent." << endl;
                    }
                }
            }
        }
    }
    cout << endl;
    cout << "The two expressions are  equivalent." << endl << endl;
}

void Satifiable() {
    bool sat = false;
    bool A[2] = { false, true };
    bool B[2] = { false, true };
    bool C[2] = { false, true };
    bool g1, g2, g3, g4, g5, g6;
    while (!sat) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    g1 = (A[i] || B[j]);
                    g2 = (A[i] && B[j]);
                    g3 = ((A[i] || B[j]) && (A[i] && B[j]));
                    if (!change)
                        g4 = (B[j] && !B[j]);
                    else
                        g4 = (B[j] && B[j]);
                    g5 = (C[k] && B[j]);
                    g6 = (A[i] || C[k]);
                    if ((g1 && g2 && g3 && g4 && g5 && g6) == 1) {
                        sat = true;
                        break;
                    }
                }
            }
        }
        break;
    }
    if (!sat) {
        change = true;
        cout << endl;
        cout << "The logical circuit is not satisfiable" << endl;
        cout << "The changed is removing the not gate for (B & ~B) to (B & B)" << endl;
        cout << endl;
    }
    else
        cout << "The logical circuit is satisfiable" << endl;
}

int main() {
    bool A[2] = { false, true };
    bool B[2] = { false, true };
    bool C[2] = { false, true };
    string a, b, c, notb, ans;
    cout << "Enter first input to the first OR gate: ";
    cin >> a;
    cout << "Enter second input to the first OR gate: ";
    cin >> b;
    cout << "Enter first input to the first AND gate: ";
    cin >> a;
    cout << "Enter second input to the first AND gate: ";
    cin >> b;
    cout << "Enter first input to the second AND gate: ";
    cin >> b;
    cout << "Enter second input to the second AND gate: ";
    cin >> notb; 
    cout << "Enter first input to the third AND gate: ";
    cin >> b;
    cout << "Enter second input to the third AND gate: ";
    cin >> c;
    cout << endl;
    cout << "Digital Logic Circuit Simplification" << endl;
    cout << endl;
    change = false;
    printTruthTable(change, A,B,C);
    Satifiable();
    cout << "Do you want to make the logical circuit satisfiable? (Y/N)" << endl;
    cin >> ans;
    if (ans == "Y" || ans == "y") {
        printTruthTable(change, A, B, C); // modification
        Satifiable();
    }
    return 0;
}

