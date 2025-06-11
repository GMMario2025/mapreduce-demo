#include "utils/string.h"
#include "${mapper_class_name}.h"
#include "${reducer_class_name}.h"

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
  std::vector<mr::string> lines;
  mr::string line;
  while (std::getline(std::cin, line))
    lines.push_back(line);
  /* Step 1: Map the token.
     Input string: "An An My Me An An My He My My An My"
     Output: [{"An", 1}, {"An", 1}, {"My", 1}, {"Me", 1}, 
              {"An", 1}, {"An", 1}, {"My", 1}, {"He", 1},
              {"My", 1}, {"My", 1}, {"An", 1}, {"My", 1}]
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
  /* Step 2: Shuffle the KV pairs. 
     Input pairs: [{"An", 1}, {"An", 1}, {"My", 1}, {"Me", 1}, 
                   {"An", 1}, {"An", 1}, {"My", 1}, {"He", 1},
                   {"My", 1}, {"My", 1}, {"An", 1}, {"My", 1}]
     Output: [{"An", [1, 1, 1, 1, 1]}, {"He", [1]}, {"Me", [1]},
              {"My", [1, 1, 1, 1, 1]}]
  */
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
  /* Step 3: Reduce the KV pairs.
     Input: [{"An", [1, 1, 1, 1, 1]}, {"He", [1]}, {"Me", [1]},
             {"My", [1, 1, 1, 1, 1]}]
     Output: [{"An", 5}, {"He", 1}, {"Me", 1}, {"My", 5}]
   */
  ${reducer_class_name} reducer;
  using OK = typename ${reducer_class_name}::output_keytype;
  using OV = typename ${reducer_class_name}::output_valuetype;
  std::vector<std::pair<OK, OV>> out;
  for (auto kv : suf_res)
    out.push_back(reducer.reduce(kv.first, kv.second));
  /* Step 4: Print the result. */
  freopen(output_path, "w", stdout);
  for (auto kv : out)
    std::cout << kv.first << '\t' << kv.second << std::endl;
  return 0;
}