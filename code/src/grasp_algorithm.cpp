#include "../include/grasp_algorithm.h"

#include <algorithm>
#include <limits>
#include <random>
#include <vector>

#include "../include/utils.h"

Solution GraspAlgorithm::construct(const ProblemInstance& instance, int m,
                                   int lrc_size) {
  int n = instance.getNumberOfElements();
  int k = instance.getDimension();
  const auto& points = instance.getPoints();

  std::vector<int> selectedIndexes;
  std::vector<bool> selected(n, false);

  std::vector<double> center(k, 0.0);

  // Inicializar generador aleatorio
  std::random_device rd;
  std::mt19937 gen(rd());

  while (selectedIndexes.size() < static_cast<size_t>(m)) {
    // Recalcular centro
    if (!selectedIndexes.empty()) {
      std::fill(center.begin(), center.end(), 0.0);   // Reiniciar centro
      for (int idx : selectedIndexes) {
        for (int i = 0; i < k; ++i) {
          center[i] += points[idx][i];
        }
      }
      for (int i = 0; i < k; ++i) {
        center[i] /= static_cast<double>(selectedIndexes.size());
      }
    } else {
      // Centro inicial: centro de todos los puntos
      std::fill(center.begin(), center.end(), 0.0);
      for (const auto& point : points) {
        for (int i = 0; i < k; ++i) {
          center[i] += point[i];
        }
      }
      for (int i = 0; i < k; ++i) {
        center[i] /= static_cast<double>(n);
      }
    }

    // Crear lista de candidatos no seleccionados
    std::vector<std::pair<int, double>> candidates;
    for (int i = 0; i < n; ++i) {
      if (!selected[i]) {
        double dist = calculateEuclideanDistance(points[i], center);
        candidates.emplace_back(i, dist);
      }
    }

    // Ordenar candidatos por distancia descendente
    std::sort(candidates.begin(), candidates.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    // Crear LRC (los mejores lrc_size elementos)
    int actualLRCSize = std::min(lrc_size, static_cast<int>(candidates.size()));
    std::uniform_int_distribution<> dis(0, actualLRCSize - 1);
    int randomIndex = dis(gen);

    int chosen = candidates[randomIndex].first;

    selectedIndexes.push_back(chosen);
    selected[chosen] = true;
  }

  Solution solution(selectedIndexes, instance, 0.0, m, lrc_size, 0);
  return solution;
}
