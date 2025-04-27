#ifndef GRASP_ALGORITHM_H
#define GRASP_ALGORITHM_H

#include "solution.h"
#include "problem_instance.h"

class GraspAlgorithm {
  public:
    // Método propio de GRASP: necesita LRC size
    Solution construct(const ProblemInstance& instance, int m, int lrc_size);
};

#endif // GRASP_ALGORITHM_H
