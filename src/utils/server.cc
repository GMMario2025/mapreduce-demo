#include "server.h"

#include <unistd.h>

namespace mr
{
  Server::Server(int port)
  {
    // Create socket.
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // Determine the address.
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
  }

  void Server::get_connection()
  {
    // Listen.
    bind(server_fd, (sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 5);
    // Get client connection.
    sockaddr_in client_addr{};
    socklen_t addr_len = sizeof(client_addr);
    client_socket = accept(
        server_fd, (sockaddr *)&client_addr, &addr_len);
  }

  String Server::get_msg()
  {
    char buf[1024] = {0};
    recv(client_socket, buf, sizeof(buf), 0);
    return String(buf);
  }

  void Server::close_server()
  {
    close(client_socket);
    close(server_fd);
  }
}