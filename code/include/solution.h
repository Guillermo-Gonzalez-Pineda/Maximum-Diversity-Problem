#ifndef SOLUTION_H
#define SOLUTION_H

#include "problem_instance.h"
#include <vector>
#include <string>

class Solution {
  public:
    // Constructor
    Solution(const std::vector<int>& selected, const ProblemInstance& instance, 
             double cpu_time = 0.0, int m = 0, int lrc_size = 0, int iteration = 0);

    // Setters
    void setCPUTime(double cpu_time);
    void setM(int m);
    void setLRCSize(int lrc_size);
    void setIteration(int iteration);

    // Getters
    const std::vector<int>& getSelectedElements() const;
    double getValue() const;
    double getCPUTime() const;
    int getM() const;
    int getLRCSize() const;
    int getIteration() const;

    std::string toString() const;

  private:
    std::vector<int> selected_;
    double value_;
    double cpu_time_;
    int m_;
    int lrc_size_;
    int iteration_;

    double evaluate(const ProblemInstance& instance) const;
};

#endif // SOLUTION_H
