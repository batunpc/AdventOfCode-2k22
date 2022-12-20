#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(int, char **) {
  std::ifstream puzzle_input("input.txt");
  std::string lines;
  std::vector<int> sum_of_numbers;
  int sum_of_cal = 0;

  if (puzzle_input.is_open()) {
    while (std::getline(puzzle_input, lines)) {
      if (!lines.empty()) {
        sum_of_cal += std::stoi(lines);
      } else {
        sum_of_numbers.push_back(sum_of_cal);
        sum_of_cal = 0;
      }
    }
    sum_of_numbers.push_back(sum_of_cal);
    puzzle_input.close();

    int max = *std::max_element(sum_of_numbers.begin(), sum_of_numbers.end());
    std::cout << "Highest Cal: " << max << std::endl;
  } else {
    std::cout << "Unable to open the puzzle";
  }
}
