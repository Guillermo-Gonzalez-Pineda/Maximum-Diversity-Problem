#ifndef GREEDY_ALGORITHM_H
#define GREEDY_ALGORITHM_H

#include "solution.h"
#include "problem_instance.h"

class GreedyAlgorithm {
  public:
    Solution construct(const ProblemInstance& instance, int m);
};

#endif // GREEDY_ALGORITHM_H
