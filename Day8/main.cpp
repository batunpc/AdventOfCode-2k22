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

  // edge
  void printEdgeTrees() {
    markEdgeTrees();
    for (const std::vector<Tree>& tree_row : trees) {
      for (const Tree& tree : tree_row) {
        if (tree.isVisible) {
          std::cout << "V";
          // std::cout << tree.height;
        } else {
          std::cout << "N";
          // std::cout << " ";
        }
      }
      std::cout << std::endl;
    }
  }

private:
  std::vector<std::vector<Tree>> trees;  // row of trees

  void parseTreeGrid(const std::vector<std::string>& input) {
    for (const std::string& line : input) {
      std::vector<Tree> tree_row;
      for (const char& c : line) {
        Tree tree;
        tree.height = c - '0';  // Convert char digit to int
        tree.isVisible = false;
        tree_row.push_back(tree);
      }
      trees.push_back(tree_row);
    }
  }

  void markEdgeTrees() {
    for (int i = 0; i < trees.size(); i++) {
      trees[i].front().isVisible = true;
      trees[i].back().isVisible = true;
    }
    for (Tree& tree : trees.front()) {
      tree.isVisible = true;
    }
    for (Tree& tree : trees.back()) {
      tree.isVisible = true;
    }
  }
};

int main() {
  auto input = sdds::read("input.txt");
  Forest forest(input);

  forest.printEdgeTrees();

  return 0;
}
