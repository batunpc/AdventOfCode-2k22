#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <vector>

int part1(std::vector<std::string> lines) {
  int sum_of_cal, max = 0;
  for (auto line : lines) {
    if (!line.empty()) {
      sum_of_cal += std::stoi(line);
    } else {
      if (sum_of_cal > max) {
        max = sum_of_cal;
      }
      sum_of_cal = 0;
    }
  }
  return max;
}

int part2(std::vector<std::string> lines) {
  int highest[3] = {0, 0, 0};
  int sum_of_cal = 0;

  for (auto line : lines) {
    if (!line.empty()) {
      sum_of_cal += std::stoi(line);
    } else {
      if (sum_of_cal > highest[0]) {
        highest[0] = sum_of_cal;
      } else if (sum_of_cal > highest[1]) {
        highest[1] = sum_of_cal;
      } else if (sum_of_cal > highest[2]) {
        highest[2] = sum_of_cal;
      }
      sum_of_cal = 0;
    }
  }
  return highest[0] + highest[1] + highest[2];
}

int main(int, char **) {
  auto lines = sdds::read("input.txt");

  std::cout << "Part 1: " << part1(lines) << std::endl;
  std::cout << "Part 2: " << part2(lines) << std::endl;
  return 0;
}
