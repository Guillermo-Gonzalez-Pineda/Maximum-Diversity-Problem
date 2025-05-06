#include "../include/table_generator.h"
#include <iostream>
#include <iomanip>

void TableGenerator::printSolutions(const std::vector<Solution>& solutions, const std::string& problemName, int n, int k) {
  std::cout << std::left
            << std::setw(16) << "Problema"
            << std::setw(8)  << "n"
            << std::setw(8)  << "K"
            << std::setw(8)  << "m"
            << std::setw(10) << "z"
            << std::setw(30) << "S"
            << std::setw(16) << "CPU"
            << "\n";

  for (const auto& solution : solutions) {
    std::cout << std::left
              << std::setw(16) << problemName
              << std::setw(8)  << n
              << std::setw(8)  << k
              << std::setw(8)  << solution.getM()
              << std::setw(10) << std::fixed << std::setprecision(2) << solution.getValue()
              << std::setw(30) << solution.toString()
              << std::setw(16) << std::setprecision(8) << solution.getCPUTime()
              << "\n";
  }

  std::cout << "-----------------------------------------------------------------\n";
}



void TableGenerator::printGraspSolutions(const std::vector<Solution>& solutions, const std::string& problemName, int n, int k) {
  std::cout << std::left
            << std::setw(16) << "Problema"
            << std::setw(8)  << "n"
            << std::setw(8)  << "K"
            << std::setw(8)  << "m"
            << std::setw(10) << "Iter"
            << std::setw(8)  << "|LRC|"
            << std::setw(10) << "z"
            << std::setw(30) << "S"
            << std::setw(16) << "CPU"
            << "\n";

  for (const auto& solution : solutions) {
    std::cout << std::left
              << std::setw(16) << problemName
              << std::setw(8)  << n
              << std::setw(8)  << k
              << std::setw(8)  << solution.getM()
              << std::setw(10) << solution.getIteration()
              << std::setw(8)  << solution.getLRCSize()
              << std::setw(10) << std::fixed << std::setprecision(2) << solution.getValue()
              << std::setw(30) << solution.toString()
              << std::setw(16) << std::setprecision(8) << solution.getCPUTime()
              << "\n";
  }

  std::cout << "-----------------------------------------------------------------\n\n";
}



void TableGenerator::printSolutionsWithNodes(const std::vector<Solution>& solutions,
                                            const std::string& problemName,
                                            int n, int k,
                                            const std::vector<int>& nodesGenerated) {
  std::cout << std::left
  << std::setw(16) << "Problema"
  << std::setw(8) << "n"
  << std::setw(8) << "K"
  << std::setw(8) << "m"
  << std::setw(10) << "z"
  << std::setw(30) << "S"
  << std::setw(16) << "CPU"
  << "Nodos" << "\n";

  for (size_t i = 0; i < solutions.size(); ++i) {
    const Solution& sol = solutions[i];
    std::cout << std::left
              << std::setw(16) << problemName
              << std::setw(8) << n
              << std::setw(8) << k
              << std::setw(8) << sol.getM()
              << std::setw(10) << std::fixed << std::setprecision(2) << sol.getValue()
              << std::setw(30) << sol.toString()
              << std::setw(16) << std::setprecision(8) << sol.getCPUTime()
              << nodesGenerated[i] << "\n";
  }

  std::cout << "-----------------------------------------------------------------\n";
}
