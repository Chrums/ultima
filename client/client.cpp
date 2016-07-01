#include "UltimaConfig.h"

#include "GameClient.h"
#include "ClientConnection.h"
#include <thread>
#include <chrono>
#include <iostream>

int main(int argc, char* argv[]) {
    
    std::shared_ptr<ClientConnection> connection = GameClient::instance().connect(Ultima_GAME_HOST, Ultima_GAME_PORT);
    while (true) {
        Message message("Hello!");
        connection->send(message);
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    return 0;
    
}