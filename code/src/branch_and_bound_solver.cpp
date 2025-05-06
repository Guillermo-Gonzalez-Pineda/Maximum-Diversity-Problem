#include "../include/branch_and_bound_solver.h"
#include <limits>
#include <algorithm>
#include <numeric>
#include "../include/greedy_algorithm.h"
#include "../include/grasp_algorithm.h"

// Constructor
BranchAndBoundSolver::BranchAndBoundSolver(const ProblemInstance& instance, int m)
  : instance_(instance), m_(m), bestValue_(std::numeric_limits<double>::lowest()) {}



Solution BranchAndBoundSolver::solve(const std::string& heuristic) {
  // Paso 1: calcular cota inferior con Greedy
  Solution bestSolution;

  if (heuristic == "greedy") {
    GreedyAlgorithm greedy;
    bestSolution = greedy.construct(instance_, m_);
  } else if (heuristic == "grasp") {
    GraspAlgorithm grasp;
    bestSolution = grasp.construct(instance_, m_, 2);
  } else {
    throw std::invalid_argument("Heurística no reconocida");
  }

  double bestValue = bestSolution.getValue();

  // Paso 2: obtener todos los puntos
  int n = instance_.getNumberOfElements();
  std::vector<int> allPoints(n);
  std::iota(allPoints.begin(), allPoints.end(), 0);

  // Paso 3: inicializar nodos raíz
  std::vector<BnBNode> openList;
  for (int i = 0; i < n; ++i) {
    std::vector<int> selected = {allPoints[i]};
    std::vector<int> remaining;

    for (int j = 0; j < n; ++j) {
      if (j != i) remaining.push_back(allPoints[j]);
    }

    BnBNode root(selected, remaining, allPoints[i], 0.0);
    root.computeUpperBound(instance_, m_);

    if (root.getUpperBound() > bestValue) {
      openList.push_back(root);
      ++nodesGenerated_;
    }
  }

  // Paso 4: bucle principal
  while (!openList.empty()) {
    // Elegir el nodo con mayor cota superior
    auto bestIt = std::max_element(openList.begin(), openList.end(),
      [](const BnBNode& a, const BnBNode& b) {
        return a.getUpperBound() < b.getUpperBound();
      });

    BnBNode current = *bestIt;
    openList.erase(bestIt); // eliminamos el nodo expandido

    // Si está completo, lo evaluamos
    if (current.isComplete(m_)) {
      double realValue = 0.0;
      const auto& selected = current.getSelectedIndices();

      for (size_t i = 0; i < selected.size(); ++i) {
        for (size_t j = i + 1; j < selected.size(); ++j) {
          realValue += instance_.getDistance(selected[i], selected[j]);
        }
      }

      if (realValue > bestValue) {
        bestValue = realValue;
        bestSolution = Solution(selected, instance_, 0.0, m_, 0, 0);
      }
    } else {
      // Expandimos el nodo y añadimos hijos con cota superior > bestValue
      std::vector<BnBNode> children = current.generateChildren(instance_, m_);

      for (const auto& child : children) {
        if (child.getUpperBound() > bestValue) {
          openList.push_back(child);
          ++nodesGenerated_;
        }
      }
    }
  }

  return bestSolution;
}



Solution BranchAndBoundSolver::solveMod(const std::string& heuristic) {
  Solution bestSolution;

  if (heuristic == "greedy") {
    GreedyAlgorithm greedy;
    bestSolution = greedy.construct(instance_, m_);
  } else if (heuristic == "grasp") {
    GraspAlgorithm grasp;
    bestSolution = grasp.construct(instance_, m_, 2);
  } else {
    throw std::invalid_argument("Heurística no reconocida");
  }

  double bestValue = bestSolution.getValue();

  // Paso 2: obtener todos los puntos
  int n = instance_.getNumberOfElements();
  std::vector<int> allPoints(n);
  std::iota(allPoints.begin(), allPoints.end(), 0);

  // Paso 3: inicializar nodos raíz
  std::vector<BnBNode> openList;
  for (int i = 0; i < n; ++i) {
    std::vector<int> selected = {allPoints[i]};
    std::vector<int> remaining;

    for (int j = 0; j < n; ++j) {
      if (j != i) remaining.push_back(allPoints[j]);
    }

    BnBNode root(selected, remaining, allPoints[i], 0.0);
    root.computeUpperBound(instance_, m_);

    if (root.getUpperBound() > bestValue) {
      openList.push_back(root);
      ++nodesGenerated_;
    }
  }

  // Paso 4: bucle principal
  while (!openList.empty()) {
    BnBNode current;

    if (openList.size() == 1) {
        current = openList.front();
        openList.erase(openList.begin());
    } else {
        std::sort(openList.begin(), openList.end(), 
        [](const BnBNode& a, const BnBNode& b) {
          return a.getUpperBound() > b.getUpperBound();
        });
        auto second_best_it = openList.begin() + 1;
        current = *second_best_it;
        openList.erase(second_best_it);
    }

    // Si está completo, lo evaluamos
    if (current.isComplete(m_)) {
      double realValue = 0.0;
      const auto& selected = current.getSelectedIndices();

      for (size_t i = 0; i < selected.size(); ++i) {
        for (size_t j = i + 1; j < selected.size(); ++j) {
          realValue += instance_.getDistance(selected[i], selected[j]);
        }
      }

      if (realValue > bestValue) {
        bestValue = realValue;
        bestSolution = Solution(selected, instance_, 0.0, m_, 0, 0);
      }
    } else {
      // Expandimos el nodo y añadimos hijos con cota superior > bestValue
      std::vector<BnBNode> children = current.generateChildren(instance_, m_);

      for (const auto& child : children) {
        if (child.getUpperBound() > bestValue) {
          openList.push_back(child);
          ++nodesGenerated_;
        }
      }
    }
  }

  return bestSolution;
}



// Expande un nodo generando sus hijos
void BranchAndBoundSolver::expandNode(const BnBNode& node, std::queue<BnBNode>& openList) {
  std::vector<BnBNode> children = node.generateChildren(instance_, m_);

  for (const BnBNode& child : children) {
    // Poda inmediata si la cota ya es insuficiente
    if (child.getUpperBound() > bestValue_) {
      openList.push(child);
    }
  }
}
