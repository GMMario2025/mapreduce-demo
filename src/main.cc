#include "utils/client.h"

#include <iostream>

#include <cassert>

int main(int argc, char* argv[])
{
  // Step 1: Get the path we need.
  assert(argc >= 6);
  std::string input_path = argv[1], // input path
    output_path = argv[2],          // output path
    // The path containing the mapper and reducer class definition.
    // (must be entire path)
    load_path = argv[3],
    // NOTE: The filename must be consist with class name (like Java).
    // eg. In WordCountMapper.cc and WordCountMapper.h, 
    // define class (or srtuct) WordCountMapper.
    mapper_class_name = argv[4],    // the name of mapper class
    reducer_class_name = argv[5];   // the name of reducer class
  // Step 2: Create client.
  mr::Client client(9001);
  // Step 3: Connect to the server.
  client.connect_to_server();
  // Step 4: Communicate.
  std::string msg = input_path + '\n'
    + output_path + '\n' + load_path + '\n'
    + mapper_class_name + '\n' + reducer_class_name + '\n';
  client.send_msg(msg);
  std::cout << "Message has passed to the master node." << std::endl; 
  // Step 5: Close connection.
  client.close_connection();
  return 0;
}