#ifndef BRANCH_AND_BOUND_SOLVER_H
#define BRANCH_AND_BOUND_SOLVER_H

#include "bnb_node.h"
#include "solution.h"
#include "problem_instance.h"
#include <queue>

// Clase que ejecuta el algoritmo de Ramificación y Poda
class BranchAndBoundSolver {
  public:
    // Constructor
    BranchAndBoundSolver(const ProblemInstance& instance, int m);
    // Ejecuta el algoritmo y devuelve la mejor solución encontrada
    Solution solve(const std::string& initialSolutionMethod);
    Solution solveMod(const std::string& initialSolutionMethod);
    int getNodesGenerated() const { return nodesGenerated_; }

  private:
    const ProblemInstance& instance_;
    int m_; // Tamaño de la solución buscada
    double bestValue_;
    int nodesGenerated_ = 0;
    // Expande un nodo y actualiza la mejor solución si procede
    void expandNode(const BnBNode& node, std::queue<BnBNode>& openList);
};

#endif // BRANCH_AND_BOUND_SOLVER_H
