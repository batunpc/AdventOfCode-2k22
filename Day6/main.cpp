#include <iostream>
#include <set>
#include <vector>

#include "FileHandler.h"
#include "Logger.h"

constexpr int packetMarker = 4;
constexpr int messageMarker = 14;

int main(int argc, char *argv[]) {
  auto lines = sdds::read("input.txt");
  //

  for (const auto &line : lines) {
    for (size_t i = 0; i < line.size() - packetMarker; i++) {
      std::string packet = line.substr(i, packetMarker);

      std::set<char> packetSet;
      for (const auto &c : packet) {
        packetSet.insert(c);
      }

      if (packetSet.size() == packetMarker) {
        challenge::log(i + packetMarker, 1);
        break;
      }
    }
  }

  for (const auto &line : lines) {
    for (size_t i = 0; i < line.size() - messageMarker; i++) {
      std::string packet = line.substr(i, messageMarker);

      std::set<char> packetSet;
      for (const auto &c : packet) {
        packetSet.insert(c);
      }

      if (packetSet.size() == messageMarker) {
        challenge::log(i + messageMarker, 2);
        break;
      }
    }
  }
}