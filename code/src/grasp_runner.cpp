#include "../include/grasp_runner.h"

#include <chrono>

#include "../include/grasp_algorithm.h"

Solution GraspRunner::run(const ProblemInstance& instance, int m, int lrc_size,
                          int iterations) {
  Solution bestSolution({}, instance);  // Solución vacía inicial
  double bestValue = -1.0;

  for (int iter = 1; iter <= iterations; ++iter) {
    GraspAlgorithm grasp;

    auto start = std::chrono::high_resolution_clock::now();
    Solution currentSolution = grasp.construct(instance, m, lrc_size);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double cpu_time = duration.count();

    currentSolution.setCPUTime(cpu_time);
    currentSolution.setM(m);
    currentSolution.setLRCSize(lrc_size);
    currentSolution.setIteration(
        iterations);  // Guardamos la cantidad de iteraciones (10 o 20, no el
                      // número individual)

    if (currentSolution.getValue() > bestValue) {
      bestValue = currentSolution.getValue();
      bestSolution = currentSolution;
    }
  }

  return bestSolution;
}
