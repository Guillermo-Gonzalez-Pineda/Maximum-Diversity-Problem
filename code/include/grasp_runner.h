#ifndef GRASP_RUNNER_H
#define GRASP_RUNNER_H

#include "problem_instance.h"
#include "solution.h"
#include <vector>

class GraspRunner {
  public:
    // Ejecuta varias veces GRASP para un (m, lrc_size) y devuelve la mejor solución
    static Solution run(const ProblemInstance& instance, int m, int lrc_size, int iterations);
};

#endif // GRASP_RUNNER_H
