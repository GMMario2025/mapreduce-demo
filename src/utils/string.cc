#include "string.h"

#include <iostream>
#include <sstream>

namespace mr
{
  std::vector<String> String::split(char delimiter) const
  {
    std::vector<String> tokens;
    String token;
    std::istringstream stream(*this);

    while (getline(stream, token, delimiter))
    {
      tokens.push_back(token);
    }

    return tokens;
  }

  void println(std::vector<String> tokens)
  {
    std::cout << '[';
    if (!tokens.empty())
    {
      std::cout << tokens[0];
      for (int i = 1; i < tokens.size(); ++i)
        std::cout << ", " << tokens[i]; 
    }
    std::cout << ']' << std::endl;
  }
}
