#include <iostream>
#include "Utils.hpp"

using namespace std;

void CalcoloPortfolio(double S, const double* w, const double* r, size_t n, double& rateOfReturn, double& V) {
    rateOfReturn = 0.0;
    for (size_t i = 0; i < n; i++) {
        rateOfReturn += w[i] * r[i];
    }
    V = (1 + rateOfReturn) * S;
}

int main() {
    string inputFile = "data.txt";
    string outputFile = "result.txt";

    double* w = nullptr;
    double* r = nullptr;
    size_t n = 0;
    double S = 0.0;

    if (!ImportVectors(inputFile, n, w, r, S)) {
        return 1;
    }

    double rateOfReturn = 0.0;
    double V = 0.0;

    CalcoloPortfolio(S, w, r, n, rateOfReturn, V);
    ExportResult(outputFile, S, n, w, r, rateOfReturn, V);

    delete[] w;
    delete[] r;

    return 0;
}
