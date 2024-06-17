#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <set>
#include "hex_tile.hpp"
#include "vertex.hpp"
#include "edge.hpp"
#include "player.hpp"

class Board {
public:
    std::vector<HexTile> hexes;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    std::set<std::pair<std::string, int>> validLocations;
    std::map<int, ResourceType> resourceTiles;

    Board();
    void addSpot(const Resource& resource, int resourceNumber);
    void addRoad(int spot1Index, int spot2Index, const std::string& playerName);
    void addSettlement(const std::string& playerName, const std::string& place, int placeNum);
    bool isValidLocation(const std::string& place, int placeNum) const;
    bool isPlaceOccupied(const std::string& place, int placeNum) const;
    void distributeResources(int diceRoll, std::vector<Player>& players);
    void printBoard() const;
    int getSpotIndex(const std::string& place, int placeNum) const;
    int getAdjacentSpotIndex(const std::string& place, int placeNum, int direction) const;
};

#endif
