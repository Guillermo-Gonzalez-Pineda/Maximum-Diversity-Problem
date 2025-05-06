#ifndef BNB_NODE_H
#define BNB_NODE_H

#include "problem_instance.h"

// Clase que representa un nodo del árbol de ramificación y poda
class BnBNode {                  // Cota superior del nodo
  public:
    // Constructor
    BnBNode() = default;
    BnBNode(const std::vector<int>& selected,
            const std::vector<int>& remaining,
            int lastAdded,
            double z1);

    // Devuelve true si la solución parcial ya está completa (m elementos)
    bool isComplete(int m) const;

    // Calcula la cota superior del nodo
    void computeUpperBound(const ProblemInstance& instance, int m);

    // Genera los nodos hijos (añadiendo un nuevo punto al conjunto seleccionado)
    std::vector<BnBNode> generateChildren(const ProblemInstance& instance, int m) const;

    // Getters
    const std::vector<int>& getSelectedIndices() const { return selectedIndices_; }
    const std::vector<int>& getRemainingIndices() const { return remainingIndices_; }
    double getZ1() const { return z1_; }
    double getUpperBound() const { return upperBound_; }
    int getLastAdded() const { return lastAdded_; }

  private:
  std::vector<int> selectedIndices_;      // Índices seleccionados en la solución parcial
  std::vector<int> remainingIndices_;     // Índices que aún pueden usarse
  int lastAdded_;                         // Último índice añadido (para mantener orden)
  double z1_;                             // Suma de distancias entre puntos seleccionados
  double upperBound_;   
};

#endif // BNB_NODE_H
