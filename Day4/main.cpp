#include "FileHandler.h"
#include <iostream>
#include <set>
#include <sstream>

std::vector<std::string> tokenizer(std::string line, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(line);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

std::vector<std::string> getPairedData(const std::vector<std::string> &lines,
                                       int digit) {
  std::vector<std::string> groups;
  for (size_t i = 0; i < lines.size(); i += digit) {
    for (int j = 0; j < digit; j++) {
      groups.push_back(lines[i + j]);
    }
  }
  return groups;
}

auto getRange(const std::string &range) {
  int hyphen = range.find('-');
  std::vector<int> rangeArr;

  int start = std::stoi(range.substr(0, hyphen));
  int end = std::stoi(range.substr(hyphen + 1));

  for (int i = start; i <= end; i++) {
    rangeArr.push_back(i);
  }
  return rangeArr;
}

int part1(const std::vector<std::string> &lines,
          const std::vector<std::string> groups) {
  size_t count = 0;

  for (auto i : groups) {
    auto tokens = tokenizer(i, ',');
    const auto &range1 = getRange(tokens[0]);
    const auto &range2 = getRange(tokens[1]);

    if (range1.back() <= range2.back() && range1.front() >= range2.front() ||
        range1.back() >= range2.back() && range1.front() <= range2.front()) {
      count++;
    }
  }
  return count;
}

int part2(const std::vector<std::string> &lines,
          const std::vector<std::string> groups) {

  size_t count = 0;
  for (auto i : groups) {
    auto tokens = tokenizer(i, ',');
    const auto &range1 = getRange(tokens[0]);
    const auto &range2 = getRange(tokens[1]);

    std::set<int> s(range1.begin(), range1.end());
    for (auto j : range2) {
      if (s.find(j) != s.end()) {
        count++;
        break;
      }
    }
  }
  return count;
}

int main(int argc, char *argv[]) {
  auto lines = sdds::read("input.txt");
  std::vector<std::string> groups = getPairedData(lines, 2);

  std::cout << "Part 1: " << part1(lines, groups) << std::endl;
  std::cout << "Part 2: " << part2(lines, groups) << std::endl;
}