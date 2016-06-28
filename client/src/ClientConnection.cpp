#include "ClientConnection.h"

void ClientConnection::process(char* buffer, size_t bytes_transferred) {
    
}

void ClientConnection::connected() {
    
}

void ClientConnection::disconnected() {
    
}

ClientConnection::ClientConnection(boost::asio::io_service& io_service) :
    Connection(io_service) {
    
}