#include "board.hpp"
#include <iostream>

Board::Board() {
    resourceTiles[2] = ResourceType::Wheat;
    resourceTiles[3] = ResourceType::Wool;
    resourceTiles[4] = ResourceType::Brick;
    resourceTiles[5] = ResourceType::Wood;
    resourceTiles[6] = ResourceType::Ore;
    resourceTiles[8] = ResourceType::Wheat;
    resourceTiles[9] = ResourceType::Wool;
    resourceTiles[10] = ResourceType::Brick;
    resourceTiles[11] = ResourceType::Wood;
    resourceTiles[12] = ResourceType::Ore;

    validLocations = {
        {"Wood", 5}, {"Brick", 4}, {"Wheat", 6}, {"Ore", 8}, {"Wool", 3},
        {"Wheat", 9}, {"Wood", 11}, {"Brick", 10}, {"Ore", 12}
    };

    addSpot(Resource(ResourceType::Wood, 1), 2);
    addSpot(Resource(ResourceType::Brick, 1), 4);
    addSpot(Resource(ResourceType::Wheat, 1), 1);
    addSpot(Resource(ResourceType::Ore, 1), 8);
    addSpot(Resource(ResourceType::Wool, 1), 3);
    addSpot(Resource(ResourceType::Wheat, 1), 9);
    addSpot(Resource(ResourceType::Wood, 1), 2);
    addSpot(Resource(ResourceType::Brick, 1), 10);
    addSpot(Resource(ResourceType::Ore, 1), 1);
    addSpot(Resource(ResourceType::Wood, 1), 5);
    addSpot(Resource(ResourceType::Brick, 1), 4);
    addSpot(Resource(ResourceType::Wheat, 1), 6);
    addSpot(Resource(ResourceType::Ore, 1), 8);
    addSpot(Resource(ResourceType::Wool, 1), 3);
    addSpot(Resource(ResourceType::Wheat, 1), 9);
    addSpot(Resource(ResourceType::Wood, 1), 11);
    addSpot(Resource(ResourceType::Brick, 1), 10);
    addSpot(Resource(ResourceType::Ore, 1), 12);

    for (int i = 0; i < 12; ++i) {
        vertices.emplace_back(i, 0);
    }
}

void Board::addSpot(const Resource& resource, int resourceNumber) {
    std::cout << "Adding spot: " << resource.toString() << " " << resourceNumber << std::endl;
    hexes.emplace_back(resource, resourceNumber, std::make_pair(0, 0)); // You may want to adjust the position
}

void Board::addRoad(int spot1Index, int spot2Index, const std::string& playerName) {
    if (spot1Index >= 0 && spot1Index < vertices.size() && spot2Index >= 0 && spot2Index < vertices.size()) {
        edges.emplace_back(&vertices[spot1Index], &vertices[spot2Index]);
        vertices[spot1Index].addRoad(&edges.back());
        vertices[spot2Index].addRoad(&edges.back());
    }
}

void Board::addSettlement(const std::string& playerName, const std::string& place, int placeNum) {
    for (auto& vertex : vertices) {
        if (vertex.position.first == placeNum && vertex.position.second == 0) { // Adjust the second coordinate as needed
            vertex.placeSettlement(playerName);
            break;
        }
    }
}

bool Board::isValidLocation(const std::string& place, int placeNum) const {
    return validLocations.find({place, placeNum}) != validLocations.end();
}

bool Board::isPlaceOccupied(const std::string& place, int placeNum) const {
    for (const auto& vertex : vertices) {
        if (vertex.position.first == placeNum && vertex.position.second == 0 && vertex.isOccupied()) {
            return true;
        }
    }
    return false;
}

void Board::distributeResources(int diceRoll, std::vector<Player>& players) {
    for (auto& hex : hexes) {
        if (hex.numberToken == diceRoll) {
            for (auto& vertex : vertices) {
                if (vertex.position == hex.position && vertex.isOccupied()) {
                    for (auto& player : players) {
                        if (player.name == vertex.owner) {
                            player.resources[hex.resource.type]++;
                            std::cout << player.name << " receives " << hex.resource.toString() << " from " << hex.resource.toString() << " " << hex.numberToken << std::endl;
                        }
                    }
                }
            }
        }
    }
}

void Board::printBoard() const {
    std::cout << "Printing Board:" << std::endl;
    for (const auto& hex : hexes) {
        std::cout << "Hex (" << hex.position.first << ", " << hex.position.second << "): "
                  << hex.resource.toString() << " " << hex.numberToken << std::endl;
    }
    for (const auto& vertex : vertices) {
        std::cout << "Vertex (" << vertex.position.first << ", " << vertex.position.second << "): "
                  << vertex.building << " owned by " << vertex.owner << std::endl;
    }
    for (const auto& edge : edges) {
        std::cout << "Edge between (" << edge.vertex1->position.first << ", " << edge.vertex1->position.second << ") and ("
                  << edge.vertex2->position.first << ", " << edge.vertex2->position.second << "): "
                  << "owned by " << edge.roadOwner << std::endl;
    }
    std::cout << "End of Board Print" << std::endl;
}

int Board::getSpotIndex(const std::string& place, int placeNum) const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i].position.first == placeNum && vertices[i].position.second == 0) { // Adjust the second coordinate as needed
            return i;
        }
    }
    return -1;
}

int Board::getAdjacentSpotIndex(const std::string& place, int placeNum, int direction) const {
    return (placeNum + 1) % vertices.size();
}
