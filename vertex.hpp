#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>
#include "resource.hpp"

class Edge;

class Vertex {
public:
    std::pair<int, int> position;
    std::string owner;
    std::string building;
    std::vector<Edge*> connectedEdges;

    Vertex(int x, int y) : position(x, y), owner(""), building("") {}

    bool isOccupied() const {
        return !owner.empty();
    }

    void placeSettlement(const std::string& playerName) {
        owner = playerName;
        building = "Settlement";
    }

    void placeCity() {
        building = "City";
    }

    void addRoad(Edge* edge) {
        connectedEdges.push_back(edge);
    }
};

#endif
