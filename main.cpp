#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

// Разложение
void choleskyDecomposition(const vector<vector<double>>& A, vector<vector<double>>& L) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;
            for (int k = 0; k < j; k++) {
                sum += L[i][k] * L[j][k];
            }
            if (i == j) {
                L[i][j] = sqrt(A[i][i] - sum);
            } else {
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
}

// Ly = b
void forwardSubstitution(const vector<vector<double>>& L, const vector<double>& b, vector<double>& y) {
    int n = L.size();
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }
}

// L транс x = y
void backwardSubstitution(const vector<vector<double>>& L, const vector<double>& y, vector<double>& x) {
    int n = L.size();
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += L[j][i] * x[j];
        }
        x[i] = (y[i] - sum) / L[i][i];
    }
}

int main() {

    ifstream inputFile("C:\\Users\\dimas\\CLionProjects\\Metod_Holeckogo\\input.txt");
    ofstream outputFile("C:\\Users\\dimas\\CLionProjects\\Metod_Holeckogo\\output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error with reading file" << endl;
        return 1;
    }

    int n;
    inputFile >> n;

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> A[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        inputFile >> b[i];
    }

    vector<vector<double>> L(n, vector<double>(n, 0));
    try {
        choleskyDecomposition(A, L);
    } catch (const runtime_error& e) {
        outputFile << "method error: " << e.what() << endl;
        return 1;
    }

    vector<double> y(n);
    forwardSubstitution(L, b, y);

    vector<double> x(n);
    backwardSubstitution(L, y, x);

    outputFile << "system solution:" << endl;
    for (int i = 0; i < n; i++) {
        outputFile << "x[" << i << "] = " << x[i] << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
