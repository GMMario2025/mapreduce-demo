#include "string.h"

#include <arpa/inet.h>

namespace mr {
  struct Client {
    int sock;
    sockaddr_in serv_addr{};

    // Constructor
    Client(int);

    void connect_to_server();
    void send_msg(String);
    void close_connection();
  };
}