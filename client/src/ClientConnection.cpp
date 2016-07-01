#include "ClientConnection.h"

#include <iostream>

void ClientConnection::process(char* buffer, size_t bytes_transferred) {
    
}

void ClientConnection::connected() {
    std::cout << "connected" << std::endl;
}

void ClientConnection::disconnected() {
    std::cout << "disconnected" << std::endl;
}

ClientConnection::ClientConnection(boost::asio::io_service& io_service) :
    Connection(io_service) {
    
}