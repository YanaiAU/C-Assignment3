#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include <string>

enum class DevelopmentCardType {
    Knight,
    VictoryPoint,
    RoadBuilding,
    YearOfPlenty,
    Monopoly
};

class DevelopmentCard {
public:
    DevelopmentCardType type;

    DevelopmentCard(DevelopmentCardType type);
    std::string toString() const;
};

#endif