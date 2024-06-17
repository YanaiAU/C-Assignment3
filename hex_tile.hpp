#ifndef HEX_TILE_HPP
#define HEX_TILE_HPP

#include <utility>
#include "resource.hpp"

class HexTile {
public:
    Resource resource;
    int numberToken;
    std::pair<int, int> position;

    HexTile(const Resource& resource, int numberToken, std::pair<int, int> position)
        : resource(resource), numberToken(numberToken), position(position) {}
};

#endif
