#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>
#include "vertex.hpp"

class Edge {
public:
    Vertex* vertex1;
    Vertex* vertex2;
    std::string roadOwner;

    Edge(Vertex* v1, Vertex* v2) : vertex1(v1), vertex2(v2), roadOwner("") {}

    void buildRoad(const std::string& playerName) {
        roadOwner = playerName;
    }
};

#endif
