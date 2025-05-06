#include "../include/bnb_node.h"
#include <algorithm>
#include <numeric>
#include <limits>

// Constructor del nodo
BnBNode::BnBNode(const std::vector<int>& selected,
                 const std::vector<int>& remaining,
                 int lastAdded,
                 double z1)
  : selectedIndices_(selected),
    remainingIndices_(remaining),
    lastAdded_(lastAdded),
    z1_(z1),
    upperBound_(0.0) // Se calculará más adelante
{}


// Devuelve true si ya se han seleccionado m elementos
bool BnBNode::isComplete(int m) const {
  return static_cast<int>(selectedIndices_.size()) == m;
}


void BnBNode::computeUpperBound(const ProblemInstance& instance, int m) {
  int needed = m - static_cast<int>(selectedIndices_.size());

  // Paso 1: Calcular z2 y z3 para cada candidato
  struct Candidate {
    int index;
    double z2;
    double z3;
    double contribution; // z2 + z3
  };

  std::vector<Candidate> candidates;

  for (int i : remainingIndices_) {
    // Calcular z2: distancia con los seleccionados
    double z2 = 0.0;
    for (int sel : selectedIndices_) {
      z2 += instance.getDistance(sel, i);
    }

    // Calcular z3: media de distancias con los k-1 más lejanos dentro de remainingIndices_
    std::vector<std::pair<int, double>> distancesToOthers;
    for (int j : remainingIndices_) {
      if (j == i) continue;
      double dist = instance.getDistance(i, j);
      distancesToOthers.push_back({j, dist});
    }

    // Ordenamos de mayor a menor y cogemos los k-1 más lejanos
    std::sort(distancesToOthers.begin(), distancesToOthers.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    int k = std::min(needed - 1, static_cast<int>(distancesToOthers.size()));
    double sumTopDistances = 0.0;
    for (int j = 0; j < k; ++j) {
      sumTopDistances += distancesToOthers[j].second;
    }

    double z3 = k > 0 ? sumTopDistances : 0.0;

    candidates.push_back({i, z2, z3, z2 + z3});
  }

  // Paso 2: seleccionar los 'needed' candidatos con mayor (z2 + z3)
  std::sort(candidates.begin(), candidates.end(),
            [](const Candidate& a, const Candidate& b) {
              return a.contribution > b.contribution;
            });

  double totalContribution = 0.0;
  for (int i = 0; i < std::min(needed, static_cast<int>(candidates.size())); ++i) {
    totalContribution += candidates[i].contribution;
  }

  upperBound_ = z1_ + totalContribution;
}



// Genera los hijos añadiendo un nuevo punto del conjunto restante
std::vector<BnBNode> BnBNode::generateChildren(const ProblemInstance& instance, int m) const {
  std::vector<BnBNode> children;

  for (int idx : remainingIndices_) {
    if (idx <= lastAdded_) continue; // Evita duplicados y mantiene orden canónico

    std::vector<int> newSelected = selectedIndices_;
    newSelected.push_back(idx);

    std::vector<int> newRemaining;
    for (int r : remainingIndices_) {
      if (r != idx) newRemaining.push_back(r);
    }

    // Calcular nuevo z1 (suma parcial)
    double newZ1 = z1_;
    for (int sel : selectedIndices_) {
      newZ1 += instance.getDistance(sel, idx);
    }

    BnBNode child(newSelected, newRemaining, idx, newZ1);
    child.computeUpperBound(instance, m);
    children.push_back(child);
  }

  // Ordenar descendente por upperBound
  std::sort(children.begin(), children.end(), 
            [](const BnBNode& a, const BnBNode& b) {
              return a.getUpperBound() > b.getUpperBound();
            });

  return children;
}


