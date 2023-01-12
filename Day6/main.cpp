#include <iostream>
#include <set>
#include <vector>

#include "FileHandler.h"
#include "Logger.h"

constexpr int packetMarker = 4;
constexpr int messageMarker = 14;

size_t countUniqueMarkerFor(const int marker, const std::string &line) {
  for (size_t i = 0; i < line.size() - marker; i++) {
    std::string packet = line.substr(i, marker);

    std::set<char> packetSet;
    for (const auto &c : packet) {
      packetSet.insert(c);
    }

    if (packetSet.size() == marker) {
      return i + marker;
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  auto lines = sdds::read("input.txt");

  for (const auto &line : lines) {
    challenge::log(countUniqueMarkerFor(packetMarker, line), 1);
    challenge::log(countUniqueMarkerFor(messageMarker, line), 2);
  }
}