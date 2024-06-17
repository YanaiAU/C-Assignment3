#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <map>
#include "vertex.hpp"
#include "edge.hpp"
#include "resource.hpp"

class Player {
public:
    std::string name;
    std::vector<Vertex*> settlements;
    std::vector<Vertex*> cities;
    std::vector<Edge*> roads;
    std::map<ResourceType, int> resources;

    Player(const std::string& name);

    void placeSettlement(Vertex& vertex);
    void placeCity(Vertex& vertex);
    void buildRoad(Edge& edge);
};

#endif
