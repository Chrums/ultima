#include "UltimaConfig.h"

#include "GameServer.h"
#include <thread>
#include <chrono>
#include <iostream>

int main(int argc, char* argv[]) {
    GameServer::instance().run(Ultima_GAME_PORT);
    while (true) std::this_thread::sleep_for (std::chrono::seconds(1));
    return 0;
}