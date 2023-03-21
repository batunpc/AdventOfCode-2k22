#include <iostream>
#include <numeric>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "FileHandler.h"
#include "Logger.h"

struct File {
  std::string path;
  int size = 0;
};

struct Directory {
  std::string path;
  int size = -1;
  std::unordered_set<std::string> subDirectories;
  std::unordered_set<std::string> subFiles;
};

class FileSystem {
private:
  std::unordered_map<std::string, Directory> allDirectories;
  std::unordered_map<std::string, File> allFiles;
  std::vector<std::string> pwd;

  int calculateDirSize(Directory &dir) {
    if (dir.size >= 0) {
      return dir.size;
    }

    auto totalSizeOfFiles = 0;
    for (const auto &path : dir.subFiles) {
      totalSizeOfFiles += allFiles[path].size;
    }

    auto totalSizeOfSubdirs = 0;
    for (const auto &path : dir.subDirectories) {
      totalSizeOfSubdirs += calculateDirSize(allDirectories.at(path));
    }

    dir.size = totalSizeOfFiles + totalSizeOfSubdirs;
    return dir.size;
  }

public:
  FileSystem() : allDirectories{{"/", Directory{"/"}}}, pwd{{"/"}} {}

  void processInput(const std::vector<std::string> &input) {
    std::regex cdre("cd\\s([a-zA-Z?\\/?..]+)");
    std::smatch match;

    for (const auto &line : input) {
      if (std::regex_search(line, match, cdre)) {
        if (line.find("/") != std::string::npos) {
          pwd.clear();            // reset and set to root
          pwd.emplace_back("/");  // cur root
        } else if (line.find("..") != std::string::npos) {
          pwd.pop_back();         // went back
        } else {
          std::string dir = match[1].str();
          pwd.emplace_back(pwd.back() + dir + "/");
        }
        // std::cout << "pwd: " << pwd.back() << std::endl;
      } else {
        auto &parent = allDirectories[pwd.back()];

        // check if file or directory
        if (line.find("dir") != std::string::npos) {
          // directory
          std::regex dirre("dir\\s([a-zA-Z?\\/?..]+)");
          std::smatch match;
          std::regex_search(line, match, dirre);
          std::string dir = match[1].str();
          auto path = pwd.back() + dir + "/";

          if (allDirectories.find(path) == allDirectories.end()) {
            allDirectories[path] = Directory{path};
          }
          parent.subDirectories.insert(path);

        } else {
          // file
          if (line.find("$") == std::string::npos) {
            // file path without size
            std::regex sizere("\\d+\\s");
            auto path = pwd.back() + std::regex_replace(line, sizere, "");

            if (allFiles.find(path) == allFiles.end()) {
              allFiles[path] = File{path, std::stoi(line)};
            }
            parent.subFiles.insert(path);
            // std::cout << "file: " << path << std::endl;
          }
        }
      }
    }
    calculateDirSize(allDirectories["/"]);
  }

  int getTotalSize() {
    auto totalSize = 0;
    for (const auto &dir : allDirectories) {
      if (dir.second.size <= 100000) {
        totalSize += dir.second.size;
      }
    }
    return totalSize;
  }

  const std::unordered_map<std::string, Directory> &getAllDirectories() const {
    return allDirectories;
  }
};

int main() {
  auto input = sdds::read("input.txt");
  FileSystem fs;
  fs.processInput(input);
  challenge::log(fs.getTotalSize(), 1);

  const auto curTotalSize = fs.getAllDirectories().at("/").size;

  constexpr auto totalSpace = 70000000;
  constexpr auto updateSize = 30000000;

  const auto unusedSpace = totalSpace - curTotalSize;
  const auto sizeToBeDeleted = updateSize - unusedSpace;

  // sort directories by size smallest to largest
  std::vector<std::pair<std::string, int>> dirs;
  for (const auto &dir : fs.getAllDirectories()) {
    dirs.emplace_back(dir.first, dir.second.size);
  }

  std::sort(dirs.begin(), dirs.end(),
            [](const auto &a, const auto &b) { return a.second < b.second; });

  for (const auto &dir : dirs) {
    if (dir.second >= sizeToBeDeleted) {
      challenge::log(dir.second, 2);
      break;
    }
  }
}