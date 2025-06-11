#include "WordCountMapper.h"

std::vector<std::pair<mr::String, mr::String>> WordCountMapper::map(mr::String line)
{
  std::vector<std::pair<mr::String, mr::String>> context;
  auto tokens = line.split(' ');
  for (auto token : tokens)
    context.push_back({token, "1"});
  return context;
}