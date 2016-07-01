#include "ServerConnection.h"

#include <iostream>

void ServerConnection::process(char* buffer, size_t bytes_transferred) {
    
}

void ServerConnection::connected() {
    std::cout << "connected" << std::endl;
}

void ServerConnection::disconnected() {
    std::cout << "disconnected" << std::endl;
}

ServerConnection::ServerConnection(boost::asio::io_service& io_service) :
    Connection(io_service) {
    
}