#include "catan.hpp"
#include <iostream>
#include <algorithm>

Catan::Catan(const std::vector<Player>& players) : players(players), currentPlayerIndex(0) {}

void Catan::chooseStartingPlayer() {
    currentPlayerIndex = rand() % players.size();
    std::cout << "Starting player: " << players[currentPlayerIndex].name << std::endl;
}

void Catan::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void Catan::printWinner() const {
    Player* winner = nullptr;
    for (const Player& player : players) {
        if (player.cities.size() * 2 + player.settlements.size() >= 10) {
            winner = const_cast<Player*>(&player);
            break;
        }
    }
    if (winner) {
        std::cout << "Winner: " << winner->name << std::endl;
    } else {
        std::cout << "No winner yet." << std::endl;
    }
}

void Catan::play() {
    chooseStartingPlayer();
    // Initial placement round 1
    std::cout << "Initial placement round 1" << std::endl;
    for (Player& player : players) {
        placeInitialSettlementAndRoad(player, false);
    }

    // Initial placement round 2 (reverse order)
    std::cout << "Initial placement round 2" << std::endl;
    for (auto it = players.rbegin(); it != players.rend(); ++it) {
        placeInitialSettlementAndRoad(*it, true);
    }

    while (true) {
        board.printBoard();
        Player& currentPlayer = players[currentPlayerIndex];

        // Roll dice
        int diceRoll = (rand() % 6 + 1) + (rand() % 6 + 1);
        std::cout << currentPlayer.name << " rolled a " << diceRoll << std::endl;

        // Distribute resources based on dice roll
        board.distributeResources(diceRoll, players);

        // Player takes actions (placeholder for now)
        // Implement trading, building, etc.
        std::cout << currentPlayer.name << "'s turn: choose an action (1: Build Settlement, 2: Build Road, 3: End Turn): ";
        int action;
        std::cin >> action;
        switch (action) {
            case 1:
                // Placeholder: Implement build settlement logic
                std::cout << "Building a settlement..." << std::endl;
                // currentPlayer.buildSettlement(board);
                break;
            case 2:
                // Placeholder: Implement build road logic
                std::cout << "Building a road..." << std::endl;
                // currentPlayer.buildRoad(board);
                break;
            case 3:
                std::cout << "Ending turn..." << std::endl;
                break;
            default:
                std::cout << "Invalid action. Ending turn by default." << std::endl;
        }

        // Check for winner
        printWinner();
        if (currentPlayer.cities.size() * 2 + currentPlayer.settlements.size() >= 10) {
            break;
        }
        nextTurn();
    }
}

void Catan::placeInitialSettlementAndRoad(Player& player, bool isSecondRound) {
    std::string place;
    int placeNum, direction;

    board.printBoard();

    while (true) {
        std::cout << player.name << ", enter location for your settlement (e.g., Ore 8): ";
        std::cin >> place >> placeNum;
        std::cout << "Checking location: " << place << " " << placeNum << std::endl;

        bool validLocation = board.isValidLocation(place, placeNum);
        bool placeOccupied = board.isPlaceOccupied(place, placeNum);

        std::cout << "isValidLocation: " << validLocation << ", isPlaceOccupied: " << placeOccupied << std::endl;

        if (!validLocation) {
            std::cout << "Invalid location. Please try again." << std::endl;
        } else if (placeOccupied) {
            std::cout << "Location occupied. Please try again." << std::endl;
        } else {
            for (Vertex& vertex : board.vertices) {
                if (vertex.position.first == placeNum && vertex.position.second == 0) { // Adjust the second coordinate as needed
                    player.placeSettlement(vertex);
                    if (isSecondRound) {
                        ResourceType resource = board.resourceTiles[placeNum];
                        player.resources[resource]++;
                        std::cout << player.name << " receives 1 " << Resource(resource, 1).toString() << " from the initial settlement." << std::endl;
                    }
                    break;
                }
            }
            break;
        }
    }

    // Place road
    while (true) {
        std::cout << player.name << ", enter location for your road (e.g., Ore 8 2): ";
        std::cin >> place >> placeNum >> direction;
        std::cout << "Checking road placement: " << place << " " << placeNum << " " << direction << std::endl;

        int spot1Index = board.getSpotIndex(place, placeNum);
        int spot2Index = board.getAdjacentSpotIndex(place, placeNum, direction);

        if (spot1Index == -1 || spot2Index == -1) {
            std::cout << "Invalid location. Please try again." << std::endl;
        } else {
            bool roadExists = false;
            for (Edge& edge : board.edges) {
                if ((edge.vertex1 == &board.vertices[spot1Index] && edge.vertex2 == &board.vertices[spot2Index]) ||
                    (edge.vertex1 == &board.vertices[spot2Index] && edge.vertex2 == &board.vertices[spot1Index])) {
                    roadExists = true;
                    if (edge.roadOwner.empty()) {
                        player.buildRoad(edge);
                        return;
                    }
                }
            }
            if (!roadExists) {
                board.edges.emplace_back(&board.vertices[spot1Index], &board.vertices[spot2Index]);
                player.buildRoad(board.edges.back());
                return;
            }
        }
    }
}
