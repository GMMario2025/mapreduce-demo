#include <vector>

namespace mr 
{
  template <typename IK, typename IV,
    typename OK, typename OV>
  struct reducer
  {
    using input_keytype = IK;
    using input_valuetype = IV;
    using output_keytype = OK;
    using output_valuetype = OV;
    std::pair<OK, OV> reduce(IK key, std::vector<IV> values);
  };
}