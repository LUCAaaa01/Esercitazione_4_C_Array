#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

bool ImportVectors(const string& inputFilePath,
                   size_t& n,
                   double*& w,
                   double*& r,
                   double& S)
{
    ifstream file(inputFilePath);
    if (!file) {
        cout << "Errore: Impossibile aprire il file " << inputFilePath << endl;
        return false;
    }

    string line;
    
    // Legge la prima riga: "S;1000"
    if (!getline(file, line)) {
        cout << "Errore: file vuoto o formato errato per S." << endl;
        return false;
    }
    size_t pos = line.find(";");
    if (pos == string::npos) {
        cout << "Errore nella lettura di S" << endl;
        return false;
    }
    S = stod(line.substr(pos + 1));

    // Legge la seconda riga: "n;8"
    if (!getline(file, line)) {
        cout << "Errore: file vuoto o formato errato per n." << endl;
        return false;
    }
    pos = line.find(";");
    if (pos == string::npos) {
        cout << "Errore nella lettura di n" << endl;
        return false;
    }
    try {
        n = stoul(line.substr(pos + 1));
    } catch (const exception& e) {
        cout << "Errore nella conversione di n: " << e.what() << endl;
        return false;
    }

    // Salta la riga di header per i vettori ("w;r")
    if (!getline(file, line)) {
        cout << "Errore: mancante header w;r." << endl;
        return false;
    }

    // Alloca gli array per w e r della dimensione n
    w = new double[n];
    r = new double[n];

    // Legge esattamente n righe contenenti i valori per w e r
    for (size_t i = 0; i < n; i++) {
        if (!getline(file, line)) {
            cout << "Errore: non ci sono abbastanza dati per i vettori." << endl;
            return false;
        }
        pos = line.find(";");
        if (pos == string::npos) {
            cout << "Errore nella lettura del file: il punto e virgola non è presente" << endl;
            return false;
        }
        try {
            w[i] = stod(line.substr(0, pos));
            r[i] = stod(line.substr(pos + 1));
        } catch (const exception& e) {
            cout << "Errore nella conversione dei valori: " << e.what() << endl;
            return false;
        }
    }
    file.close();
    return true;
}

void ExportResult(const string& outputFilePath,
                  double S, 
                  size_t n,
                  const double* w,
                  const double* r,
                  double rateOfReturn,
                  double V)
{
    ofstream file(outputFilePath);
    if (file.fail()) {
        cout << "Errore: impossibile aprire il file di output." << endl;
        return;
    }
    file << fixed << setprecision(2);
    cout << fixed << setprecision(2);

    file << "S= " << S << ",n=" << n << endl;
    cout << "S= " << S << ",n=" << n << endl;

    file << "w= [";
    cout << "w= [";
    for (size_t i = 0; i < n; i++) {
        file << w[i];
        cout << w[i];
        if (i < n - 1) {
            file << " ";
            cout << " ";
        }
    }
    file << "]" << endl;
    cout << "]" << endl;

    file << "r= [";
    cout << "r= [";
    for (size_t i = 0; i < n; i++) {
        file << r[i];
        cout << r[i];
        if (i < n - 1) {
            file << " ";
            cout << " ";
        }
    }
    file << "]" << endl;
    cout << "]" << endl;

    file << "Rate of return of the portfolio: " << setprecision(4) << rateOfReturn << endl;
    cout << "Rate of return of the portfolio: " << setprecision(4) << rateOfReturn << endl;

    file << setprecision(2) << "V: " << V << endl;
    cout << setprecision(2) << "V: " << V << endl;

    file.close();
}
