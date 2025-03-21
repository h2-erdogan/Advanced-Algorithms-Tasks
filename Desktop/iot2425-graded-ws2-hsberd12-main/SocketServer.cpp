#include "SocketServer.h"
#include <iostream>

SocketServer::SocketServer(int port, MessageHandler& handler)
    : _port(port), _messageHandler(handler) {}

void SocketServer::start() {
    std::cout << "Socket Server waiting for messages on UDP port " << _port << "...\n";
    // Buraya UDP soket dinleme kodlarını zaten yazmışsın, oraya ekleyebilirsin
}
