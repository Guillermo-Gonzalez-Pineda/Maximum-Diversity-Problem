#include "../include/table_generator.h"
#include <iostream>

void TableGenerator::printSolutions(const std::vector<Solution>& solutions, const std::string& problemName, int n, int k) {
  std::cout << "Problema\tn\tK\tm\tz\tS\tCPU\n";

  for (const auto& solution : solutions) {
      std::cout << problemName << "\t"
                << n << "\t"
                << k << "\t"
                << solution.getM() << "\t"
                << solution.getValue() << "\t"
                << solution.toString() << "\t"
                << solution.getCPUTime() << "\n";
  }

  std::cout << "-----------------------------------------------------------------\n";
}


void TableGenerator::printGraspSolutions(const std::vector<Solution>& solutions, const std::string& problemName, int n, int k) {
  std::cout << "Problema\tn\tK\tm\tIter\t|LRC|\tz\tS\tCPU\n";

  for (const auto& solution : solutions) {
      std::cout << problemName << "\t"
                << n << "\t"
                << k << "\t"
                << solution.getM() << "\t"
                << solution.getIteration() << "\t"
                << solution.getLRCSize() << "\t"
                << solution.getValue() << "\t"
                << solution.toString() << "\t"
                << solution.getCPUTime() << "\n";
  }

  std::cout << "-----------------------------------------------------------------\n\n";
}

