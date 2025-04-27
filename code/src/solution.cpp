#include "../include/solution.h"
#include <sstream>

Solution::Solution(const std::vector<int>& selected, const ProblemInstance& instance, 
                  double cpu_time, int m, int lrc_size, int iteration)
    : selected_(selected), value_(evaluate(instance)), cpu_time_(cpu_time), 
    m_(m), lrc_size_(lrc_size), iteration_(iteration) {}


// Getters

const std::vector<int>& Solution::getSelectedElements() const {
  return selected_;
}

double Solution::getValue() const {
  return value_;
}

double Solution::getCPUTime() const {
  return cpu_time_;
}

int Solution::getM() const {
  return m_;
}

int Solution::getLRCSize() const {
  return lrc_size_;
}

int Solution::getIteration() const {
  return iteration_;
}


// Setters

void Solution::setCPUTime(double cpu_time) {
  cpu_time_ = cpu_time;
}

void Solution::setM(int m) {
  m_ = m;
}

void Solution::setLRCSize(int lrc_size) {
  lrc_size_ = lrc_size;
}

void Solution::setIteration(int iteration) {
  iteration_ = iteration;
}

double Solution::evaluate(const ProblemInstance& instance) const {
  double sum = 0.0;
  for (size_t i = 0; i < selected_.size(); ++i) {
    for (size_t j = i + 1; j < selected_.size(); ++j) {
      int idx1 = selected_[i];
      int idx2 = selected_[j];
      sum += instance.getDistance(idx1, idx2);
    }
  }
  return sum;
}

std::string Solution::toString() const {
    std::ostringstream oss;
    oss << "{";
    for (size_t i = 0; i < selected_.size(); ++i) {
        oss << selected_[i];
        if (i != selected_.size() - 1) {
            oss << ", ";
        }
    }
    oss << "}";
    return oss.str();
}

