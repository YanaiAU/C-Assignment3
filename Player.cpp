#include "player.hpp"

Player::Player(const std::string& name) : name(name) {}

void Player::placeSettlement(Vertex& vertex) {
    settlements.push_back(&vertex);
    vertex.placeSettlement(name);
}

void Player::placeCity(Vertex& vertex) {
    cities.push_back(&vertex);
    vertex.placeCity();
}

void Player::buildRoad(Edge& edge) {
    roads.push_back(&edge);
    edge.buildRoad(name);
}
