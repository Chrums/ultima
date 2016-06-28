#include "GameServer.h"

#include <iostream>

void GameServer::client_connected(std::shared_ptr<ServerConnection> connection) {
    std::cout << "client connected" << std::endl;
}

void GameServer::client_disconnected(std::shared_ptr<ServerConnection> connection) {
    
}