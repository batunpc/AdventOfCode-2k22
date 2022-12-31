#include "FileHandler.h"
#include <iostream>
#include <map>
#include <sstream>

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

auto part1(const std::vector<std::string> &lines) {
  std::string first_half, second_half, rep;
  int sum = 0;
  auto uPoints = letterPoints();

  for (auto line : lines) {
    divider(line, &first_half, &second_half);
    rep = detectRep(first_half, second_half);

    for (auto i : rep) {
      sum += uPoints[i];
    }
  }
  return sum;
}

std::vector<std::string> splitIn(const std::vector<std::string> &lines,
                                 int digit) {
  std::vector<std::string> groups;
  for (int i = 0; i < lines.size(); i += digit) {
    std::string group;
    for (int j = 0; j < digit; j++) {
      group += lines[i + j] + " ";
    }
    groups.push_back(group);
  }
  return groups;
}

int part2(const std::vector<std::string> &lines) {
  auto groups = splitIn(lines, 3);
  std::vector<std::string> item;
  int sum = 0;
  auto uPoints = letterPoints();

  for (int i = 0; i < groups.size(); i++) {
    std::stringstream ss(groups[i]);
    std::string word;
    while (ss >> word) {
      item.push_back(word);
    }
  }

  for (int i = 0; i < item.size(); i += 3) {
    for (int j = 0; j < item[i].length(); j++) {
      if (item[i + 1].find(item[i][j]) != std::string::npos) {
        sum += uPoints[item[i][j]];
        break;
      }
    }
  }
  return sum;
}

int main(int argc, char *argv[]) {
  auto lines = sdds::read("input.txt");

  std::cout << "Part 1: " << part1(lines) << std::endl;
  std::cout << "Part 2: " << part2(lines) << std::endl;
}