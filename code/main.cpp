#include <chrono>
#include <filesystem>
#include <iostream>
#include <vector>

#include "../include/grasp_algorithm.h"
#include "../include/grasp_runner.h"
#include "../include/greedy_algorithm.h"
#include "../include/local_search.h"
#include "../include/parser_data.h"
#include "../include/solution.h"
#include "../include/table_generator.h"

namespace fs = std::filesystem;

std::vector<Solution> runGreedy(const ProblemInstance& instance) {
  std::vector<Solution> solutions;

  for (int m = 2; m <= 5; ++m) {
    GreedyAlgorithm greedy;

    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = greedy.construct(instance, m);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double cpu_time = duration.count();

    solution.setCPUTime(cpu_time);
    solution.setM(m);
    solution.setLRCSize(0);
    solution.setIteration(0);

    solutions.push_back(solution);
  }

  return solutions;
}

std::vector<Solution> runGreedyWithLocalSearch(
    const ProblemInstance& instance) {
  std::vector<Solution> solutions;

  for (int m = 2; m <= 5; ++m) {
    GreedyAlgorithm greedy;

    auto startGreedy = std::chrono::high_resolution_clock::now();
    Solution initialSolution = greedy.construct(instance, m);
    auto endGreedy = std::chrono::high_resolution_clock::now();

    Solution improvedSolution =
        LocalSearch::improveSolution(initialSolution, instance);
    auto endLocalSearch = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = endLocalSearch - startGreedy;
    double cpu_time = duration.count();

    improvedSolution.setCPUTime(cpu_time);
    improvedSolution.setM(m);
    improvedSolution.setLRCSize(0);
    improvedSolution.setIteration(0);

    solutions.push_back(improvedSolution);
  }

  return solutions;
}

std::vector<Solution> runGrasp(const ProblemInstance& instance) {
  std::vector<Solution> solutions;
  std::vector<int> lrc_sizes = {2, 3};
  std::vector<int> iteration_blocks = {10, 20};

  for (int m = 2; m <= 5; ++m) {
    for (int lrc_size : lrc_sizes) {
      for (int iterations : iteration_blocks) {
        Solution bestSolution =
            GraspRunner::run(instance, m, lrc_size, iterations);
        bestSolution.setM(m);
        bestSolution.setLRCSize(lrc_size);
        bestSolution.setIteration(iterations);

        solutions.push_back(bestSolution);
      }
    }
  }

  return solutions;
}

std::vector<Solution> runGraspWithLocalSearch(const ProblemInstance& instance) {
  std::vector<Solution> solutions;
  std::vector<int> lrc_sizes = {2, 3};
  std::vector<int> iteration_blocks = {10, 20};

  for (int m = 2; m <= 5; ++m) {
    for (int lrc_size : lrc_sizes) {
      for (int iterations : iteration_blocks) {
        Solution bestSolution =
            GraspRunner::run(instance, m, lrc_size, iterations);

        Solution improvedSolution =
            LocalSearch::improveSolution(bestSolution, instance);

        improvedSolution.setM(m);
        improvedSolution.setLRCSize(lrc_size);
        improvedSolution.setIteration(iterations);

        solutions.push_back(improvedSolution);
      }
    }
  }

  return solutions;
}

int main() {
  TableGenerator generator;

  std::cout << "================================================================\n";
  std::cout << "GREEDY\n";
  std::cout << "================================================================\n";
  for (const auto& entry : fs::directory_iterator("../../data/")) {
    if (entry.is_regular_file() && entry.path().extension() == ".txt") {
      std::string filepath = entry.path().string();
      std::string filename = entry.path().stem().string();

      ParserData parser;
      ProblemInstance instance = parser.parseFile(filepath);
      int n = instance.getNumberOfElements();
      int k = instance.getDimension();

      auto greedy_solutions = runGreedy(instance);
      generator.printSolutions(greedy_solutions, filename, n, k);
    }
  }

  std::cout << "================================================================\n";
  std::cout << "GREEDY + LOCAL SEARCH\n";
  std::cout << "================================================================\n";
  for (const auto& entry : fs::directory_iterator("../../data/")) {
    if (entry.is_regular_file() && entry.path().extension() == ".txt") {
      std::string filepath = entry.path().string();
      std::string filename = entry.path().stem().string();

      ParserData parser;
      ProblemInstance instance = parser.parseFile(filepath);
      int n = instance.getNumberOfElements();
      int k = instance.getDimension();

      auto greedy_ls_solutions = runGreedyWithLocalSearch(instance);
      generator.printSolutions(greedy_ls_solutions, filename, n, k);
    }
  }

  std::cout << "================================================================\n";
  std::cout << "GRASP\n";
  std::cout << "================================================================\n";
  for (const auto& entry : fs::directory_iterator("../../data/")) {
    if (entry.is_regular_file() && entry.path().extension() == ".txt") {
      std::string filepath = entry.path().string();
      std::string filename = entry.path().stem().string();

      ParserData parser;
      ProblemInstance instance = parser.parseFile(filepath);
      int n = instance.getNumberOfElements();
      int k = instance.getDimension();

      auto grasp_ls_solutions = runGraspWithLocalSearch(instance);
      generator.printGraspSolutions(grasp_ls_solutions, filename, n, k);
    }
  }

  return 0;
}
