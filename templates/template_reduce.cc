#include "utils/string.h"
#include "udf/${reducer_class_name}.h"

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
  ${reducer_class_name} reducer;
  using IK = typename ${reducer_class_name}::input_keytype;
  using IV = typename ${reducer_class_name}::input_valuetype;
  // Get shuffle result.
  std::vector<std::pair<IK, std::vector<IV>>> suf_res;
  for (auto line : lines)
  {
    auto tokens = line.split(' ');
    std::pair<IK, std::vector<IV>> kv;
    kv.first = tokens[0];
    tokens.erase(tokens.begin());
    kv.second = tokens;
    suf_res.push_back(kv);
  }
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
