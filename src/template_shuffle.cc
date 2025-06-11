/*************************************************
 This file just handle the shuffle operation.
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
  // Get type (expermential)
  using K = typename ${mapper_class_name}::keytype;
  using V = typename ${mapper_class_name}::valuetype;
  std::vector<std::pair<K, V>> kvs;
  for (auto line : lines)
  {
    auto tokens = line.split(' ');
    kvs.push_back({tokens[0], tokens[1]});
  }
  // Shuffle.
  std::sort(kvs.begin(), kvs.end());
  std::vector<std::pair<K, std::vector<V>>> suf_res;
  std::pair<K, std::vector<V>> item = {kvs[0].first, {kvs[0].second}};
  for (int i = 1; i < kvs.size(); ++i)
  {
    if (kvs[i] != kvs[i - 1])
    {
      suf_res.push_back(item);
      item = {kvs[i].first, {kvs[i].second}};
    }
    else
      item.second.push_back(kvs[i].second);
  }
  suf_res.push_back(item);
  // Output.
  freopen(output_path, "w", stdout);
  for (auto it : suf_res)
  {
    std::cout << it.first << ' ';
    for (auto v : it.second)
      std::cout << v << ' ';
    std::cout << std::endl;
  }
  return 0;
}