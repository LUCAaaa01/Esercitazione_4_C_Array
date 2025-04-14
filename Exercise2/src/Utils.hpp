#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
using namespace std;

bool ImportVectors(const string& inputFilePath,
                   size_t& n,
                   double*& w,
                   double*& r,
                   double& S);

void ExportResult(const string& outputFilePath,
                  double S, 
                  size_t n,
                  const double* w,
                  const double* r,
                  double rateOfReturn,
                  double V);

#endif
