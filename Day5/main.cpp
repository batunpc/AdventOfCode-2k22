#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <vector>

#include "FileHandler.h"

using Stacks = std::vector<std::stack<char>>;
using Lines = std::vector<std::string>;

const int getNumOfStacks(const std::string &lastLine) {
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

// auto empty_line = Lines::iterator{};
auto empty_line = Lines::iterator{};

Stacks parseStacks(const Lines &lines, const std::string &stack_labels) {
  auto stacks = Stacks{};

  for (int i = 0; i < stack_labels.size(); i++) {
    if (stack_labels[i] == ' ') {
      continue;
    }

    auto current_stack = std::stack<char>{};

    for (auto it = empty_line - 2; it != lines.begin() - 1; it--) {
      const auto &line = *it;
      const auto &crate = line[i];
      if (crate == ' ') {
        break;
      }
      current_stack.push(crate);
    }
    stacks.emplace_back(current_stack);
  }

  return stacks;
}

void printStacks(const Stacks &stacks) {
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

void processMoves(const Lines &lines, Stacks &stacks) {
  for (auto it = empty_line + 1; it != lines.end(); it++) {
    const auto &line = *it;

    std::stringstream ss(line);
    std::string word;
    std::vector<int> numbers;
    while (ss >> word) {
      if (std::isdigit(word[0])) {
        numbers.push_back(std::stoi(word));
      }
    }
    int amo = numbers[0];
    int from = numbers[1];
    int to = numbers[2];
    // std::cout << "Move crate(s) " << numbers[0] << " from stack " <<
    // numbers[1]
    //          << " to stack " << numbers[2] << std::endl;
    while (amo > 0) {
      stacks[to - 1].push(stacks[from - 1].top());
      stacks[from - 1].pop();
      amo--;
    }
  }
}

int main(int argc, char *argv[]) {
  auto lines = sdds::read("input.txt");
  // find empty line from the entire file
  empty_line = std::find(lines.begin(), lines.end(), "");
  // get the labels <num>
  const auto &stack_labels = *(empty_line - 1);
  // get the largest number in the labels
  const int no_of_stacks = getNumOfStacks(stack_labels);
  std::cout << "Number of stacks: " << no_of_stacks << std::endl;

  // create the stacks
  auto stacks = parseStacks(lines, stack_labels);

  // print the stacks
  // printStacks(stacks);

  processMoves(lines, stacks);

  std::cout << "Final state: " << std::endl;

  for (int i = 0; i < stacks.size(); i++) {
    std::cout << stacks[i].top();
  }
  std::cout << std::endl;
}
