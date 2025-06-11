#include "string.h"

#include <netinet/in.h>

namespace mr
{
  struct Server {
    int server_fd;
    sockaddr_in addr{};
    int client_socket;

    // Constructor
    Server(int port);

    void get_connection();
    String get_msg();
    void close_server();
  };
}
