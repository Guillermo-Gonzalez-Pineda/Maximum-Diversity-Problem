#include "../include/greedy_algorithm.h"
#include "../include/utils.h"
#include <vector>
#include <limits>
#include <algorithm>

Solution GreedyAlgorithm::construct(const ProblemInstance& instance, int m) {
  int numberOfPoints = instance.getNumberOfElements();
  int kDimension = instance.getDimension();
  const auto& points = instance.getPoints();

  // Inicializar subconjunto seleccionado
  std::vector<int> selectedIndices;
  std::vector<bool> selected(numberOfPoints, false);

  // 1. Calcular centro de gravedad inicial
  std::vector<double> center(kDimension, 0.0);
  for (const auto& point : points) {
    for (int i = 0; i < kDimension; ++i) {
      center[i] += point[i];
    }
  }
  for (int i = 0; i < kDimension; ++i) {
    center[i] /= static_cast<double>(numberOfPoints);
  }

  // 2. Elegir primer elemento (más alejado del centro)
  int first = -1;
  double maxDist = -1.0;
  for (int i = 0; i < numberOfPoints; ++i) {
    double dist = calculateEuclideanDistance(points[i], center);
    if (dist > maxDist) {
      maxDist = dist;
      first = i;
    }
  }
  selectedIndices.push_back(first);
  selected[first] = true;

  // 3. Iterativamente añadir elementos
  while (selectedIndices.size() < static_cast<size_t>(m)) {
    // Recalcular centro de gravedad de los elementos seleccionados
    std::vector<double> newCenter(kDimension, 0.0);
    for (int idx : selectedIndices) {
      for (int i = 0; i < kDimension; ++i) {
        newCenter[i] += points[idx][i];
      }
    }
    for (int i = 0; i < kDimension; ++i) {
      newCenter[i] /= static_cast<double>(selectedIndices.size());
    }

    // Buscar el elemento no seleccionado más alejado del nuevo centro
    int next = -1;
    double maxDist = -1.0;
    for (int i = 0; i < numberOfPoints; ++i) {
      if (!selected[i]) {
        double dist = calculateEuclideanDistance(points[i], newCenter);
        if (dist > maxDist) {
          maxDist = dist;
          next = i;
        }
      }
    }

    selectedIndices.push_back(next);
    selected[next] = true;
  }

  // Crear la solución
  Solution solution(selectedIndices, instance);
  return solution;
}
