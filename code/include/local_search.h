#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "problem_instance.h"
#include "solution.h"

class LocalSearch {
public:
  static Solution improveSolution(const Solution& initialSolution, const ProblemInstance& instance);
};

#endif // LOCAL_SEARCH_H
