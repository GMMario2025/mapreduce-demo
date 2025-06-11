#include "client.h"

#include <unistd.h>

namespace mr
{
  Client::Client(int port)
  {
    // Create socket.
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
  }

  void Client::connect_to_server()
  {
    connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr));
  }

  void Client::send_msg(String msg)
  {
    send(sock, msg.c_str(), msg.length(), 0);
  }

  void Client::close_connection()
  {
    close(sock);
  }
}