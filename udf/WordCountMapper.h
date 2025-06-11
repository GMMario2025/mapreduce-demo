#include "mr/mapper.h"

struct WordCountMapper : public mr::mapper<mr::String, mr::String>
{
  std::vector<std::pair<mr::String, mr::String>> map(mr::String line);
};