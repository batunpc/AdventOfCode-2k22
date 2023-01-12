#include "FileHandler.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> sdds::read(const std::string &filename,
                                    char delimiter) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "\033[1;31m Error:\033[0m"
              << " Failed to open file: "
              << "\033[1;34m" << filename << "\033[0m" << std::endl;
    return {};
  }
  std::stringstream file_contents;
  file_contents << file.rdbuf();
  file.close();

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file_contents, line, delimiter)) {
    lines.push_back(line);
  }
  return lines;
}
