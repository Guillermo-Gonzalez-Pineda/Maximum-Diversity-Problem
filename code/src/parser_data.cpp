#include "../include/parser_data.h"
#include "../include/utils.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

ProblemInstance ParserData::parseFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file " + filename);
  }

  int n, k;
  file >> n >> k;
  std::string line;
  std::getline(file, line);
  std::vector<std::vector<double>> points(n, std::vector<double>(k));
  // Leer todos los puntos
  for (int i = 0; i < n; ++i) {
  std::getline(file, line);

  // Reemplazar comas por puntos
  std::replace(line.begin(), line.end(), ',', '.');

  std::istringstream iss(line);
  for (int j = 0; j < k; ++j) {
    iss >> points[i][j];
    points[i][j] = roundToTwoDecimals(points[i][j]);
  }
}

  // Calcular matriz de distancias
  std::vector<std::vector<double>> distances(n, std::vector<double>(n, 0.0));
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double dist = calculateEuclideanDistance(points[i], points[j]);
      dist = roundToTwoDecimals(dist);
      distances[i][j] = dist;
      distances[j][i] = dist;
    }
  }

  file.close();
  return ProblemInstance(n, k, points, distances);
}
