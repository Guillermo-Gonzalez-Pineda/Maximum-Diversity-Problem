#ifndef PROBLEM_INSTANCE_H
#define PROBLEM_INSTANCE_H

#include <vector>

class ProblemInstance {
  public:
    // Constructor
    ProblemInstance(int numberOfElements, int kDimension, 
                    const std::vector<std::vector<double>>& points, 
                    const std::vector<std::vector<double>>& distances);

    // Getters
    int getNumberOfElements() const;
    int getDimension() const;
    const std::vector<std::vector<double>>& getPoints() const;
    double getDistance(int i, int j) const;

  private:
    int numberOfElements_;
    int kDimension_;
    std::vector<std::vector<double>> points_;
    std::vector<std::vector<double>> distances_;
};

#endif // PROBLEM_INSTANCE_H
