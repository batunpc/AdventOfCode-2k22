#include <iostream>
#include <vector>

#include "FileHandler.h"
#include "Logger.h"

class Tree {
public:
  int height = 0;
  bool isVisible = true;
};

class Forest {
public:
  Forest(const std::vector<std::string> &input) { parseTreeGrid(input); }

  void printTreeGrid() const {
    for (const std::vector<Tree> &tree_row : trees) {
      for (const Tree &tree : tree_row) {
        std::cout << tree.height;
      }
      std::cout << std::endl;
    }
  }

  // edge
  int printVisibleTrees() {
    markEdgeTrees();
    markInteriorTrees();
    for (const std::vector<Tree> &tree_row : trees) {
      for (const Tree &tree : tree_row) {
        if (tree.isVisible) {
          // std::cout << "V";
          num_of_visible_trees++;
        } else {
          // std::cout << "N";
        }
      }
      // std::cout << std::endl;
    }
    return num_of_visible_trees;
  }

private:
  std::vector<std::vector<Tree>> trees;  // row of trees
  int num_of_visible_trees = 0;

  void parseTreeGrid(const std::vector<std::string> &input) {
    for (const std::string &line : input) {
      std::vector<Tree> tree_row;
      for (const char &c : line) {
        Tree tree;
        tree.height = c - '0';  // Convert char digit to int
        tree.isVisible = false;
        tree_row.push_back(tree);
      }
      trees.push_back(tree_row);
    }
  }

  void markEdgeTrees() {
    for (auto &tree_row : trees) {
      tree_row.front().isVisible = true;
      tree_row.back().isVisible = true;
    }
    for (Tree &tree : trees.front()) {
      tree.isVisible = true;
    }
    for (Tree &tree : trees.back()) {
      tree.isVisible = true;
    }
  }

  void markInteriorTrees() {
    for (int i = 0; i < trees.size(); i++) {    // row
      for (int j = 0; j < trees.size(); j++) {  // col
        if (i == 0 || i == trees.size() - 1 || j == 0 ||
            j == trees[i].size() - 1) {
          continue;
        }
        int current_height = trees[i][j].height;

        auto visibleFromLeft = [](const std::vector<Tree> &tree_row,
                                  const int &col) {
          for (int k = col - 1; k >= 0; k--) {
            if (tree_row[k].height >= tree_row[col].height) {
              return false;
            }
          }
          return true;
        };

        auto visibleFromRight = [](const std::vector<Tree> &tree_row,
                                   const int &col) {
          for (int k = col + 1; k < tree_row.size(); k++) {
            if (tree_row[k].height >= tree_row[col].height) {
              return false;
            }
          }
          return true;
        };

        auto visibleFromUp = [](const std::vector<std::vector<Tree>> &trees,
                                const int &row, const int &col) {
          for (int k = row - 1; k >= 0; k--) {
            if (trees[k][col].height >= trees[row][col].height) {
              return false;
            }
          }
          return true;
        };

        auto visibleFromDown = [](const std::vector<std::vector<Tree>> &trees,
                                  const int &row, const int &col) {
          for (int k = row + 1; k < trees.size(); k++) {
            if (trees[k][col].height >= trees[row][col].height) {
              return false;
            }
          }
          return true;
        };

        if (visibleFromLeft(trees[i], j) || visibleFromRight(trees[i], j) ||
            visibleFromUp(trees, i, j) || visibleFromDown(trees, i, j)) {
          trees[i][j].isVisible = true;
        }
      }
    }
  };
};
int main() {
  auto input = sdds::read("input.txt");
  Forest forest(input);

  challenge::log(forest.printVisibleTrees(), 1);

  return 0;
}
