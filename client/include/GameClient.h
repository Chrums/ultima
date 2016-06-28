#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include "Client.h"
#include "ClientConnection.h"

class GameClient : public Client<GameClient, ClientConnection> {
public:
    GameClient() = default;
    void client_connected(std::shared_ptr<ClientConnection> connection);
    void client_disconnected(std::shared_ptr<ClientConnection> connection);
};

#endif