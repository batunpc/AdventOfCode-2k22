#include <iostream>
#include <sstream>

#include "FileHandler.h"
#include "Logger.h"

class Tree {
public:
  int height = 0;
  bool isVisible = true;
};

class Forest {
public:
  Forest(const std::vector<std::string>& input) { parseTreeGrid(input); }
  void printTreeGrid() const {
    for (const std::vector<Tree>& tree_row : trees) {
      for (const Tree& tree : tree_row) {
        std::cout << tree.height;
      }
      std::cout << std::endl;
    }
  }

private:
  std::vector<std::vector<Tree>> trees;

  void parseTreeGrid(const std::vector<std::string>& input) {
    for (const std::string& line : input) {
      std::vector<Tree> tree_row;
      for (const char& c : line) {
        Tree tree;
        tree.height = c - '0';  // Convert char digit to int
        tree_row.push_back(tree);
      }
      trees.push_back(tree_row);
    }
  }
};

int main() {
  auto input = sdds::read("input.txt");
  Forest forest(input);

  return 0;
}
