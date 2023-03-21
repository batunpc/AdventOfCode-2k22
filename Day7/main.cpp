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

auto allDirectories = std::unordered_map<std::string, Directory>{};
auto allFiles = std::unordered_map<std::string, File>{};

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

int main(int argc, char *argv[]) {
  auto input = sdds::read("input.txt");

  std::regex cdre("cd\\s([a-zA-Z?\\/?..]+)");
  std::smatch match;

  allDirectories["/"] = Directory{"/"};

  auto pwd = std::vector<std::string>{{"/"}};

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

  auto totalSize = 0;
  // std::cout << "Directories with size <= 100000:" << std::endl;
  for (const auto &dir : allDirectories) {
    if (dir.second.size <= 100000) {
      totalSize += dir.second.size;
      std::cout << dir.second.path << " " << dir.second.size << std::endl;
    }
  }
  challenge::log(totalSize, 1);
}