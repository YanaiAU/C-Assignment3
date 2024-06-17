#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

enum class ResourceType {
    Wood,
    Brick,
    Wheat,
    Ore,
    Wool
};

class Resource {
public:
    ResourceType type;
    int quantity;

    Resource(ResourceType type, int quantity);
    std::string toString() const;
};

#endif
