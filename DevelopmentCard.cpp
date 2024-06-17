#include "DevelopmentCard.hpp"

DevelopmentCard::DevelopmentCard(DevelopmentCardType type) : type(type) {}

std::string DevelopmentCard::toString() const {
    switch (type) {
        case DevelopmentCardType::Knight: return "Knight";
        case DevelopmentCardType::VictoryPoint: return "Victory Point";
        case DevelopmentCardType::RoadBuilding: return "Road Building";
        case DevelopmentCardType::YearOfPlenty: return "Year of Plenty";
        case DevelopmentCardType::Monopoly: return "Monopoly";
        default: return "Unknown";
    }
}
