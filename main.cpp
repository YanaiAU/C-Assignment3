#include <iostream>
#include <vector>
#include "board.hpp"
#include "player.hpp"
#include "catan.hpp"

int main() {
    Board board;

    std::vector<Player> players;
    std::string playerName;

    while (players.size() < 4) {
        std::cout << "Enter player name (or type 'start' to begin the game if there are at least 3 players): ";
        std::cin >> playerName;

        if (playerName == "start" && players.size() >= 3) {
            break;
        } else if (playerName == "start" && players.size() < 3) {
            std::cout << "You need at least 3 players to start the game." << std::endl;
        } else {
            players.push_back(Player(playerName));
            std::cout << "Player " << playerName << " added. Total players: " << players.size() << std::endl;

            if (players.size() == 4) {
                std::cout << "Maximum players reached. Starting the game..." << std::endl;
                break;
            }
        }
    }

    Catan catan(players);

    catan.play();

    return 0;
}
