#include "../include/utils.h"
#include <cmath>

double calculateEuclideanDistance(const std::vector<double>& a, const std::vector<double>& b) {
  double sum = 0.0;
  for (size_t i = 0; i < a.size(); ++i) {
    double diff = a[i] - b[i];
    sum += diff * diff;
  }
  return std::sqrt(sum);
}

double roundToTwoDecimals(double value) {
  return std::round(value * 100.0) / 100.0;
}
