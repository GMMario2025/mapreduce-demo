#include <iostream>

#include "utils/client.h"
#include "utils/server.h"

int main()
{
  while (true)
  {
    mr::Server server(9001);
    // Step 2: Get connection.
    server.get_connection();
    // Step 3: Get the message.
    mr::String msg = server.get_msg();
    std::cout << "Get: " << msg << std::endl;
    // Step 4: Transfer map task to the worker.
    mr::Client client(9002);
    client.connect_to_server();
    client.send_msg(msg + "Map");
    client.close_connection();
    server.close_server();
    mr::Server server_2(9001);
    server_2.get_connection();
    mr::String response = server_2.get_msg();
    std::cout << "Get: " << response << std::endl;
    std::cout << response << std::endl;
    std::cout << "Try to send reduce ..." << std::endl;
    // Step 5: Transfer reduce task to the worker.
    mr::Client client_2(9002);
    client_2.connect_to_server();
    client_2.send_msg(msg + "Reduce");
    client_2.close_connection();
    server_2.close_server();
  }
  return 0;
}