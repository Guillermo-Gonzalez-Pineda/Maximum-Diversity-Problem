#include "../include/problem_instance.h"

ProblemInstance::ProblemInstance(int n, int k, 
                                const std::vector<std::vector<double>>& points, 
                                const std::vector<std::vector<double>>& distances)
  : numberOfElements_(n), kDimension_(k), points_(points), distances_(distances) {}

int ProblemInstance::getNumberOfElements() const {
  return numberOfElements_;
}

int ProblemInstance::getDimension() const {
  return kDimension_;
}

const std::vector<std::vector<double>>& ProblemInstance::getPoints() const {
  return points_;
}

double ProblemInstance::getDistance(int i, int j) const {
  return distances_[i][j];
}
