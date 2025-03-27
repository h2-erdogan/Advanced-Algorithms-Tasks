#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include "MessageHandler.h"

class SocketServer {
public:
    SocketServer(int port, MessageHandler& handler);  // 👈 Eklenen constructor
    void start();

private:
    int _port;
    MessageHandler& _messageHandler;
};

#endif
