#include "FileHandler.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <vector>

int getNumOfStacks(const std::string &lastLine) {
  int number_of_stacks = 0;
  std::stringstream ss(lastLine);
  while (ss) {
    int number;
    ss >> number;
    if (number > number_of_stacks) {
      number_of_stacks = number;
    }
  }
  return number_of_stacks;
}

std::pair<std::vector<std::stack<char>>, std::string>
createStacks(const std::vector<std::string> &lines) {
  auto empty_line = std::find(lines.begin(), lines.end(), "");
  // get the line before the empty line (the labels <num>)
  const auto &stack_labels = *(empty_line - 1);
  // get the largest number in the labels
  const int no_of_stacks = getNumOfStacks(stack_labels);
  std::cout << "Number of stacks: " << no_of_stacks << std::endl;

  auto stacks = std::vector<std::stack<char>>{};

  for (int i = 0; i < stack_labels.size(); i++) {
    if (stack_labels[i] == ' ') {
      continue;
    }

    auto current_stack = std::stack<char>{};

    for (auto lineIndex = empty_line - 2; lineIndex != lines.begin() - 1;
         lineIndex--) {
      const auto &line = *lineIndex;
      const auto &crate = line[i];
      if (crate == ' ') {
        break;
      }
      current_stack.push(crate);
    }
    stacks.emplace_back(current_stack);
  }

  return {stacks, stack_labels};
}

void printStacks(const std::vector<std::stack<char>> &stacks,
                 const std::string &stackLabels) {
  for (int i = 0; i < stacks.size(); i++) {
    std::cout << "Stack " << i + 1 << ": ";
    auto temp_stack = stacks[i];
    while (!temp_stack.empty()) {
      std::cout << temp_stack.top() << " ";
      temp_stack.pop();
    }
    std::cout << std::endl;
  }
}

int main(int argc, char *argv[]) {

  const auto lines = sdds::read("input.txt");
  const auto [stacks, stackLabels] = createStacks(lines);
  printStacks(stacks, stackLabels);
}
