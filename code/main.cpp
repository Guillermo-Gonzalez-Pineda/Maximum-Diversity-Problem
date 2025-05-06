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
#include "../include/branch_and_bound_solver.h"

namespace fs = std::filesystem;

std::vector<Solution> runGreedy(const ProblemInstance& instance) {
  std::vector<Solution> solutions;

  for (int m = 2; m <= 5; ++m) {
    GreedyAlgorithm greedy;

    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = greedy.construct(instance, m);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
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

    Solution improvedSolution = LocalSearch::improveSolution(initialSolution, instance);
    auto endLocalSearch = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = endLocalSearch - startGreedy;
    double cpu_time = duration.count();

    improvedSolution.setCPUTime(cpu_time);
    improvedSolution.setM(m);
    improvedSolution.setLRCSize(0);
    improvedSolution.setIteration(0);

    solutions.push_back(improvedSolution);
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
        auto start = std::chrono::high_resolution_clock::now();

        Solution bestSolution = GraspRunner::run(instance, m, lrc_size, iterations);
        Solution improvedSolution = LocalSearch::improveSolution(bestSolution, instance);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        improvedSolution.setCPUTime(duration.count());
        improvedSolution.setM(m);
        improvedSolution.setLRCSize(lrc_size);
        improvedSolution.setIteration(iterations);

        solutions.push_back(improvedSolution);
      }
    }
  }

  return solutions;
}

namespace fs = std::filesystem;

// ... (runGreedy, runGreedyWithLocalSearch, runGrasp, runGraspWithLocalSearch sin cambios)

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " <modo>\n";
    std::cerr << "  <modo>: approx | exact\n";
    return 1;
  }

  std::string mode = argv[1];
  TableGenerator generator;

  if (mode == "approx") {
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
    std::cout << "GRASP + LOCAL SEARCH\n";
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

  } else if (mode == "exact") {
    std::vector<std::string> heuristics = {"greedy", "grasp"};
    for (const auto& heuristic : heuristics) {
      std::cout << "================================================================\n";
      std::cout << "BRANCH AND BOUND (EXACTO)" << heuristic << "\n";
      std::cout << "================================================================\n";

      for (const auto& entry : fs::directory_iterator("../../data/")) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
          std::string filepath = entry.path().string();
          std::string filename = entry.path().stem().string();

          ParserData parser;
          ProblemInstance instance = parser.parseFile(filepath);
          int n = instance.getNumberOfElements();
          int k = instance.getDimension();

          std::vector<Solution> exact_solutions;
          std::vector<int> nodesGenerated;

          for (int m = 2; m <= 5; ++m) {
            BranchAndBoundSolver solver(instance, m);
            auto start = std::chrono::high_resolution_clock::now();
            Solution sol = solver.solve(heuristic);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> duration = end - start;
            sol.setCPUTime(duration.count());
            sol.setM(m);
            sol.setLRCSize(0);
            sol.setIteration(0);
            exact_solutions.push_back(sol);
            nodesGenerated.push_back(solver.getNodesGenerated());
          }

          generator.printSolutionsWithNodes(exact_solutions, filename, n, k, nodesGenerated);
        }
      }
    }

  } else if (mode == "exact_mod") {
    std::cout << "================================================================\n";
    std::cout << "BRANCH AND BOUND (MODIFICADO - SEGUNDO MEJOR NODO)\n";
    std::cout << "================================================================\n";
  
    for (const auto& entry : fs::directory_iterator("../../data/")) {
      if (entry.is_regular_file() && entry.path().extension() == ".txt") {
        std::string filepath = entry.path().string();
        std::string filename = entry.path().stem().string();
  
        ParserData parser;
        ProblemInstance instance = parser.parseFile(filepath);
        int n = instance.getNumberOfElements();
        int k = instance.getDimension();
  
        std::vector<Solution> modified_solutions;
        std::vector<int> nodesGenerated;
  
        for (int m = 2; m <= 5; ++m) {
          BranchAndBoundSolver solver(instance, m);
  
          auto start = std::chrono::high_resolution_clock::now();
          Solution sol = solver.solveMod("greedy");
          auto end = std::chrono::high_resolution_clock::now();
  
          std::chrono::duration<double, std::milli> duration = end - start;
          sol.setCPUTime(duration.count());
          sol.setM(m);
          sol.setLRCSize(0);
          sol.setIteration(0);
          modified_solutions.push_back(sol);
          nodesGenerated.push_back(solver.getNodesGenerated());
        }
  
        generator.printSolutionsWithNodes(modified_solutions, filename, n, k, nodesGenerated);
      }
    }
  }

  return 0;
}
