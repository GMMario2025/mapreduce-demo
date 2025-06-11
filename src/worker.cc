#include <fstream>
#include <iostream>

#include "utils/server.h"
#include "utils/client.h"

int main()
{
  // Create a server and receive the message from master.
  mr::Server server(9002);
  while (true)
  {
    server.get_connection();
    mr::String msg = server.get_msg();
    // Just output it.
    auto tokens = msg.split('\n');
    mr::println(tokens);
    mr::String line;
    if (tokens[5] == "Map")
    {
      system("mkdir -p /tmp/out");
      // Read the map template.
      std::ifstream mapInFile("src/template_map.cc");
      mr::String mapCode;
      while (std::getline(mapInFile, line))
        mapCode += line + '\n';
      // Input the mapper class.
      size_t pos = 0;
      while ((pos = mapCode.find("${mapper_class_name}", pos)) != mr::String::npos)
      {
        mapCode.replace(pos, 20, tokens[3]);
        pos += tokens[3].length();
      }
      // Create the map task file.
      std::ofstream mapOutFile("/tmp/task_map.cc");
      mapOutFile << mapCode;
      mr::String compile_cmd = "g++ /tmp/task_map.cc " + tokens[2] + '/' + tokens[3] + ".cc src/utils/string.cc -o /tmp/task_map -I src -I .";
      system(compile_cmd.c_str());
      // Execute it!
      mr::String exe_cmd = "/tmp/task_map " + tokens[0] + " /tmp/out/map_out.txt";
      system(exe_cmd.c_str());

      // Tell the master node that map has finished.
      std::cout << "Finished map!" << std::endl;
      mr::Client client(9001);
      client.connect_to_server();
      client.send_msg("OK");
      client.close_connection();
    }
    else if (tokens[5] == "Reduce")
    {
      // Read the shuffle template.
      std::ifstream shuffleInFile("src/template_shuffle.cc");
      mr::String shuffleCode;
      while (std::getline(shuffleInFile, line))
        shuffleCode += line + '\n';
      size_t pos = 0;
      while ((pos = shuffleCode.find("${mapper_class_name}", pos)) != mr::String::npos)
      {
        shuffleCode.replace(pos, 20, tokens[3]);
        pos += tokens[3].length();
      }
      // Create the shuffle task file.
      std::ofstream shuffleOutFile("/tmp/task_shuffle.cc");
      shuffleOutFile << shuffleCode;
      mr::String compile_cmd = "g++ /tmp/task_shuffle.cc " + tokens[2] + '/' + tokens[3] + ".cc src/utils/string.cc -o /tmp/task_shuffle -I src -I .";
      system(compile_cmd.c_str());
      // Execute it!
      mr::String exe_cmd = "/tmp/task_shuffle /tmp/out/map_out.txt /tmp/out/shuffle_out.txt";
      system(exe_cmd.c_str());

      // Read the reduce template.
      std::ifstream reduceInFile("src/template_reduce.cc");
      mr::String reduceCode;
      while (std::getline(reduceInFile, line))
        reduceCode += line + '\n';
      pos = 0;
      while ((pos = reduceCode.find("${reducer_class_name}", pos)) != mr::String::npos)
      {
        reduceCode.replace(pos, 21, tokens[4]);
        pos += tokens[4].length();
      }
      // Create the reduce task file.
      std::ofstream reduceOutFile("/tmp/task_reduce.cc");
      reduceOutFile << reduceCode;
      compile_cmd = "g++ /tmp/task_reduce.cc " + tokens[2] + '/' + tokens[4] + ".cc src/utils/string.cc -o /tmp/task_reduce -I src -I .";
      system(compile_cmd.c_str());
      // Execute it!
      exe_cmd = "/tmp/task_reduce /tmp/out/shuffle_out.txt " + tokens[1];
      system(exe_cmd.c_str());
    }
  }
  server.close_server();
  return 0;
}