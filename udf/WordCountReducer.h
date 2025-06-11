#include "mr/reducer.h"
#include "utils/string.h"

struct WordCountReducer
    : public mr::reducer<mr::String, mr::String, mr::String, mr::String>
{
  std::pair<mr::String, mr::String> reduce(mr::String key, std::vector<mr::String> values);
};