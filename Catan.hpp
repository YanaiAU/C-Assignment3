#ifndef CATAN_HPP
#define CATAN_HPP

#include <vector>
#include "board.hpp"
#include "player.hpp"

class Catan {
public:
    std::vector<Player> players;
    Board board;
    int currentPlayerIndex;

    Catan(const std::vector<Player>& players);

    void chooseStartingPlayer();
    void nextTurn();
    void printWinner() const;
    void play();
    void placeInitialSettlementAndRoad(Player& player, bool isSecondRound);
};

#endif
