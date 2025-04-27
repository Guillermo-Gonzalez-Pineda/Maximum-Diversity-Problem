#ifndef PARSER_DATA_H
#define PARSER_DATA_H

#include <string>
#include "problem_instance.h"

class ParserData {
  public:
    ProblemInstance parseFile(const std::string& filename);
};

#endif // PARSER_DATA_H
