#ifndef TABLE_GENERATOR_H
#define TABLE_GENERATOR_H

#include <vector>
#include <string>
#include "solution.h"

class TableGenerator {
public:
  void printSolutions(const std::vector<Solution>& solutions, const std::string& problemName, int n, int k);
  void printGraspSolutions(const std::vector<Solution>& solutions, const std::string& problemName, int n, int k);

};

#endif // TABLE_GENERATOR_H
