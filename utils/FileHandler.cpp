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
