#include "FileHandler.h"
#include <fstream>
#include <iostream>

std::string sdds::read(const std::string &filename, bool print) {

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open puzzle - " << filename << std::endl;
    exit(EXIT_FAILURE);
  }
  if (print)
    std::cout << file.rdbuf() << std::endl;

  return std::string((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
}