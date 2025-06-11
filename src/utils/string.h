#pragma once
#include <string>
#include <vector>

namespace mr {
  struct String : public std::string {
    // Constructors
    String() : std::string() {}
    String(const char* s) : std::string(s) {}
    String(const std::string s) : std::string(s) {}

    // Spilt to string array
    std::vector<String> split(char delimiter) const;
  };

  void println(std::vector<String> tokens);
}