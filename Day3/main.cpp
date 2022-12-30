#include "FileHandler.h"
#include <iostream>
#include <map>

auto letterPoints() {
  std::map<char, int> points;
  int count = 0;
  for (char lower_char = 'a'; lower_char <= 'z'; ++lower_char) {
    count++;
    points[lower_char] = count;
  }
  for (char upper_char = 'A'; upper_char <= 'Z'; ++upper_char) {
    count++;
    points[upper_char] = count;
  }
  return points;
}

void divider(const std::string line, std::string *first_half,
             std::string *second_half) {
  *first_half = line.substr(0, line.length() / 2);
  *second_half = line.substr(line.length() / 2, line.length() / 2);
}

std::string detectRep(const std::string first, const std::string second) {
  std::string rep;
  for (int i = 0; i < first.length(); i++) {
    if (second.find(first[i]) != std::string::npos) {
      rep.push_back(first[i]);
      break;
    }
  }
  return rep;
}

int main(int argc, char *argv[]) {
  auto lines = sdds::read("input.txt");
  std::string first_half, second_half, rep;
  int sum;
  auto uPoints = letterPoints();

  for (auto line : lines) {
    divider(line, &first_half, &second_half);
    rep = detectRep(first_half, second_half);

    for (auto i : rep) {
      // std::cout << uPoints[i] << std::endl;
      sum += uPoints[i];
    }
  }
  std::cout << "Part 1: " << sum << std::endl;
}