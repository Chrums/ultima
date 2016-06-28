#include "UltimaConfig.h"

#include "GameClient.h"
#include <thread>
#include <chrono>
#include <iostream>

int main(int argc, char* argv[]) {
    GameClient::instance().connect(Ultima_GAME_HOST, Ultima_GAME_PORT);
    while (true) std::this_thread::sleep_for (std::chrono::seconds(1));
    return 0;
}