#include "../include/local_search.h"

#include <algorithm>
#include <vector>

Solution LocalSearch::improveSolution(const Solution& initialSolution,
                                      const ProblemInstance& instance) {
  Solution bestSolution = initialSolution;
  double bestValue = initialSolution.getValue();
  bool improvement = true;

  int n = instance.getNumberOfElements();
  std::vector<int> selected = initialSolution.getSelectedElements();
  std::vector<bool> isSelected(n, false);

  for (int idx : selected) {
    isSelected[idx] = true;
  }

  while (improvement) {
    improvement = false;
    bool found = false;

    for (int inIdx = 0; inIdx < n && !found; ++inIdx) {
      if (!isSelected[inIdx]) {                         
        for (int outIdx = 0; outIdx < selected.size() && !found; ++outIdx) {
          int currentSelected = selected[outIdx];

          selected[outIdx] = inIdx;

          Solution candidateSolution(selected, instance);
          double candidateValue = candidateSolution.getValue();

          if (candidateValue > bestValue) {
            bestValue = candidateValue;
            bestSolution = candidateSolution;
            improvement = true;
            found = true;

            isSelected[currentSelected] = false;
            isSelected[inIdx] = true;
          } else {
            selected[outIdx] = currentSelected;
          }
        }
      }
    }
  }

  return bestSolution;
}
