#include "WordCountReducer.h"

std::pair<mr::String, mr::String> WordCountReducer::reduce(mr::String key, std::vector<mr::String> values)
{
  int sum = 0;
  for (mr::String i : values)
    sum += stoi(i);
  return {key, std::to_string(sum)};
}
