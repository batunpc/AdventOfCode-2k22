#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <vector>

#include "FileHandler.h"
#include "Logger.h"

using Stacks = std::vector<std::stack<char>>;
using Lines = std::vector<std::string>;

const int getNumOfStacks(const std::string &lastLine) {
  int number_of_stacks = 0;
  for (int i = 0; i < lastLine.size(); i++) {
    if (lastLine[i] == ' ') {
      continue;
    }
    number_of_stacks++;
  }
  return number_of_stacks;
}

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

void moveBlock(Stacks &stacks, int from, int to) {
  stacks[to - 1].push(stacks[from - 1].top());
  stacks[from - 1].pop();
}

Stacks processMoves(const Lines &lines, Stacks stacks, bool reverse) {
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
    int amo = numbers[0], from = numbers[1], to = numbers[2];
    auto crates = std::vector<char>{};
    while (amo > 0) {
      auto crate = stacks[from - 1].top();
      stacks[from - 1].pop();
      crates.emplace_back(crate);
      amo--;
    }
    if (reverse) {
      for (auto it = crates.rbegin(); it != crates.rend(); it++) {
        stacks[to - 1].push(*it);
      }
    } else {
      for (auto crate : crates) {
        stacks[to - 1].push(crate);
      }
    }
  }
  return stacks;
}

void logStacks(const Stacks &stacks, const int &label) {
  std::string top_str;
  for (const auto &stack : stacks) {
    top_str += stack.top();
  }
  challenge::log(top_str, label);
}

int main(int argc, char *argv[]) {
  auto lines = sdds::read("input.txt");
  // find empty line from the entire file
  empty_line = std::find(lines.begin(), lines.end(), "");
  // get the labels <num>
  const auto &stack_labels = *(empty_line - 1);
  // get the largest number in the labels
  const int no_of_stacks = getNumOfStacks(stack_labels);
  // create the stacks
  auto stacks = parseStacks(lines, stack_labels);

  auto stacks_part1 = processMoves(lines, stacks, false);
  logStacks(stacks_part1, 1);  // part 1

  auto reverse_stacks = processMoves(lines, stacks, true);
  logStacks(reverse_stacks, 2);  // part 2
}
