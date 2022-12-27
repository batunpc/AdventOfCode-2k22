#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

int part1(std::vector<std::string> lines, char winner_table[3][2],
          char loser_table[3][2], std::map<char, int> moves) {
  unsigned int score = 0;

  for (auto line : lines) {
    for (int i = 0; i < 3; i++) {
      if (line[0] == winner_table[i][0] && line[2] == winner_table[i][1]) {
        score += moves[line[2]] + 6; // win
      }
    }
    for (int i = 0; i < 3; i++) {
      if (line[0] == loser_table[i][0] && line[2] == loser_table[i][1]) {
        score += moves[line[2]]; // lose
      }
    }

    if (moves[line[0]] == moves[line[2]]) {
      score += moves[line[2]] + 3; // draw
    }
  }
  return score;
}

int part2(std::vector<std::string> lines, std::map<char, int> moves) {
  unsigned int score = 0;

  for (auto line : lines) {
    if (line[2] == 'X') {
      if (line[0] == 'A') {
        score += moves['C'];
      } else if (line[0] == 'B') {
        score += moves['A'];
      } else if (line[0] == 'C') {
        score += moves['B'];
      }
    }
    if (line[2] == 'Y') {
      score += moves[line[0]] + 3;
    }
    if (line[2] == 'Z') {
      if (line[0] == 'A') {
        score += moves['B'] + 6;
      } else if (line[0] == 'B') {
        score += moves['C'] + 6;
      } else if (line[0] == 'C') {
        score += moves['A'] + 6;
      }
    }
  }
  return score;
}

int main(int argc, char *argv[]) {
  auto lines = sdds::read("input.txt");
  char winner_table[3][2] = {{'C', 'X'}, {'A', 'Y'}, {'B', 'Z'}};
  char loser_table[3][2] = {{'A', 'Z'}, {'B', 'X'}, {'C', 'Y'}};

  std::map<char, int> moves = {{'A', 1}, {'B', 2}, {'C', 3},
                               {'X', 1}, {'Y', 2}, {'Z', 3}};

  std::cout << "Part 1: " << part1(lines, winner_table, loser_table, moves)
            << std::endl;
  std::cout << "Part 2: " << part2(lines, moves) << std::endl;

  return 0;
}