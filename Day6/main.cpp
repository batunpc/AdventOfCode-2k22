#include <iostream>
#include <set>
#include <vector>

#include "FileHandler.h"

constexpr int packetSize = 4;
int main(int argc, char *argv[]) {
  auto lines = sdds::read("input.txt");
  //

  for (const auto &line : lines) {
    for (size_t i = 0; i < line.size() - packetSize; i++) {
      std::string packet = line.substr(i, packetSize);

      std::set<char> packetSet;
      for (const auto &c : packet) {
        packetSet.insert(c);
      }

      if (packetSet.size() == packetSize) {
        std::cout << packet << std::endl;
        std::cout << "i: " << i + packetSize << std::endl;
        break;
      }
    }
  }
}