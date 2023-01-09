#pragma once

#include <chrono>
#include <iostream>

constexpr char RESET[] = "\033[0m";
constexpr char GREEN[] = "\033[32m";
constexpr char YELLOW[] = "\033[33m";
constexpr char BLUE[] = "\033[34m";

// get directory name

namespace challenge {

  template <typename T>

  void log(const T& answer, int part, const char* color = BLUE,
           std::ostream& out = std::cout) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&now_time);
    char now_str[9];
    std::strftime(now_str, sizeof(now_str), "%T", &tm);
    std::cout << "\r";
    if (tm.tm_hour >= 6 && tm.tm_hour < 18) {
      std::cout << "👾";
    } else {
      std::cout << "🌙";
    }
    std::cout << GREEN << " (" << now_str << ") " << RESET << YELLOW << "part"
              << part << RESET << " : " << color << answer << RESET
              << std::endl;
  }
}  // namespace challenge