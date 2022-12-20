#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <map>

int main(int argc, char *argv[]) {
  std::ifstream puzzle("input.txt");
  std::string lines;
  unsigned int score = 0;

  char winner_table[3][2] = {{'C', 'X'}, {'A', 'Y'}, {'B', 'Z'}};
  char loser_table[3][2] = {{'A', 'Z'}, {'B', 'X'}, {'C', 'Y'}};

  std::map<char, int> moves = {{'A', 1}, {'B', 2}, {'C', 3},
                               {'X', 1}, {'Y', 2}, {'Z', 3}};

  if (puzzle.is_open()) {
    while (std::getline(puzzle, lines)) {
      for (int i = 0; i < 3; i++) {
        if (lines[0] == winner_table[i][0] && lines[2] == winner_table[i][1]) {
          score += moves[lines[2]] + 6; // win
        }
      }
      for (int i = 0; i < 3; i++) {
        if (lines[0] == loser_table[i][0] && lines[2] == loser_table[i][1]) {
          score += moves[lines[2]]; // lose
        }
      }

      if (moves[lines[0]] == moves[lines[2]]) {
        score += moves[lines[2]] + 3; // draw
      }
    }
    puzzle.close();
    std::cout << "Score: " << score << std::endl;
  }
}