#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include "Server.h"
#include "ServerConnection.h"

class GameServer : public Server<GameServer, ServerConnection> {
friend class Singleton;
public:
    GameServer() = default;
    void client_connected(std::shared_ptr<ServerConnection> connection);
    void client_disconnected(std::shared_ptr<ServerConnection> connection);
};

#endif