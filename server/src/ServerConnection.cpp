#include "ServerConnection.h"

void ServerConnection::process(char* buffer, size_t bytes_transferred) {
    
}

void ServerConnection::connected() {
    
}

void ServerConnection::disconnected() {
    
}

ServerConnection::ServerConnection(boost::asio::io_service& io_service) :
    Connection(io_service) {
    
}