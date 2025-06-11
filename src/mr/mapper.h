#include "utils/string.h"

namespace mr
{
  template <typename K, typename V>
  struct mapper
  {
    // Show the type.
    using keytype = K;
    using valuetype = V;
    std::vector<std::pair<K, V>> map(String line);
  };
}
