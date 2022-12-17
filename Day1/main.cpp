#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
// 1. Sum each number until you see a empty line
// 2. Store the numbers that are summed into an vector
// 3. Find the highest number from the vector and print it

std::string caloriePrinter(std::string &lines) { return lines; }

int main(int, char **) {
  std::ifstream puzzle_input("input.txt");
  std::string myline;
  std::stringstream ss;
  int value, sum = 0;

  if (puzzle_input.is_open()) {
    while (puzzle_input) {
      std::getline(puzzle_input, myline);

      std::stringstream ss;
      ss.str(myline);
      ss >> value;
      std::cout << value << " ";
      sum += value;

      if (!myline.size())
        std::cout << "\n";
    }
    std::cout << sum << "\n";
  } else {
    std::cout << "Cannot open the puzzle";
  }
}
