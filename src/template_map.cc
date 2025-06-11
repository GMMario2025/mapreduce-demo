/*************************************************
 This file just handle the map operation and save.
 *************************************************/ 

#include "utils/string.h"
#include "udf/${mapper_class_name}.h"

#include <algorithm>
#include <iostream>

#include <cassert>

int main(int argc, char *argv[])
{
  assert(argc == 3);
  char *input_path = argv[1],
    *output_path = argv[2];
  freopen(input_path, "r", stdin);
  // Input
  std::vector<mr::String> lines;
  mr::String line;
  while (std::getline(std::cin, line))
    lines.push_back(line);
  /* Map the token.
     Input string: "An An My Me An An My He My My An My"
     Output: [{"An", "1"}, {"An", "1"}, {"My", "1"}, {"Me", "1"}, 
              {"An", "1"}, {"An", "1"}, {"My", "1"}, {"He", "1"},
              {"My", "1"}, {"My", "1"}, {"An", "1"}, {"My", "1"}]
  */
  ${mapper_class_name} mapper;
  // Get the type of K and V.
  using K = typename ${mapper_class_name}::keytype;
  using V = typename ${mapper_class_name}::valuetype;
  std::vector<std::pair<K, V>> kvs;
  for (auto line : lines) {
    auto kvs_part = mapper.map(line);
    kvs.insert(kvs.end(), kvs_part.begin(), kvs_part.end());
  }
  // Output to a file for shuffle.
  freopen(output_path, "w", stdout);
  for (auto kv : kvs)
    std::cout << kv.first << ' ' << kv.second << std::endl;
  return 0;
}