#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> sdds::read(const std::string &filename, bool print) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open puzzle - " << filename << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
    if (print)
      std::cout << line << std::endl;
  }
  file.close();
  return lines;
}