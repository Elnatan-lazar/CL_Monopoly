#include "Location.hpp"
#include "Player.hpp"
#include <cmath>

// Default constructor
Location::Location() : _id(-1), _name("nothing"), _cost(-1), _type(UTILITY), _owner(nullptr) {}
//Constructor for non-property locations
Location::Location(int id, LocType type, const std::string &name, sf::Color color): _id(id), _name(name), _color(color), _type(type), _owner(nullptr) {}

Location::Location(int id, LocType type, const std::string &name, sf::Color color, int rent) : _id(id), _name(name), _color(color), _type(type), _owner(nullptr),_baseRent(rent) {

}
//Constructor for utility and train
Location::Location(int id, LocType type, const std::string &name, sf::Color color, int cost, int rent)
        : _id(id), _name(name), _color(color), _type(type), _owner(nullptr),_cost(cost),_baseRent(rent) {}

// Constructor for property locations with full details
Location::Location(int id, LocType type, const std::string &name, sf::Color color, int cost, int baseRent, int buildCost, int hotelRent, int hotelCost)
        : _id(id), _name(name), _cost(cost), _type(type), _color(color), _baseRent(baseRent),
          _houseCost(buildCost), _hotelRent(hotelRent), _hotelCost(hotelCost), _owner(nullptr) {}

// Getter methods
int Location::getCost() const { return _cost; }
int Location::getID() const { return _id; }
std::string Location::getName() const { return _name; }
int Location::getHotelCost() const { return _hotelCost; }
int Location::getHouseCost() const { return _houseCost; }
int Location::getRent() const {
    if (_hasHotel) {
        return _hotelRent;
    } else {
        return _baseRent * pow(2, _houseCount); // Rent increases with each house
    }
}
int Location::getHouseCount() const { return _houseCount; }
sf::Color Location::getColor() const { return _color; }
bool Location::hasHotel() const { return _hasHotel; }
LocType Location::getType() const { return _type; }
Player *const Location::getOwner() const { return _owner; }

// Setter methods
void Location::setID(int id) { _id = id; }
void Location::setName(const std::string &new_name) { _name = new_name; }
void Location::setOwner(Player* player) { _owner = player; }
void Location::setColour(sf::Color new_colour) { _color = new_colour; }

// Buying houses and hotels
bool Location::buyHouse() {
    if(canBuildHouse()) {
        if (_houseCount < 4) {
            _houseCount++;
            std::cout << "House bought for " << _houseCost << std::endl;
            return true;
        }
        std::cout << "Cannot buy more than 4 houses. Consider buying a hotel." << std::endl;
        return false;
    }
    else{
        return false;
    }
}

bool Location::buyHotel() {
    if(canBuildHotel()) {
        if (_houseCount == 4 && !_hasHotel) {
            _hasHotel = true;
            _houseCount = 0; // Reset house count after building a hotel
            std::cout << "Hotel bought for " << _hotelCost << std::endl;
            return true;
        }
        std::cout << "You must have 4 houses first to buy a hotel." << std::endl;
        return false;
    }
    else{
        return false;
    }
}

// Reset location to initial state
void Location::reset() {
    _houseCount = 0;
    _hasHotel = false;
    _owner = nullptr;
}


// New methods

bool Location::canBuildHouse() {
    // Check if player owns the complete set
    if (!hasCompleteSet()) {
        std::cout << "Cannot build house: complete set not owned." << std::endl;
        return false;
    }

    // Check house build rule
    int minHouseCount = getMinHouseCountInSet();
    if (_houseCount == minHouseCount) {
        return true;
    }
    std::cout << "Cannot build house: other properties in the set must have " << minHouseCount + 1 << " houses first." << std::endl;
    return false;
}

bool Location::canBuildHotel() {
    // Check if the player owns the complete set
    if (!hasCompleteSet()) {
        std::cout << "Cannot build a hotel: complete set not owned." << std::endl;
        return false;
    }

    // All properties must have 4 houses to build a hotel
    for (const auto& loc : _sameColorLocations) {
        if (loc->_houseCount < 4) {
            std::cout << "Cannot build hotel: all properties must have 4 houses." << std::endl;
            return false;
        }
    }
    return true;
}

void Location::addSameColorLocation(std::shared_ptr<Location> location) {
    if (location && location->getColor() == _color) {
        _sameColorLocations.push_back(location);
    }
}

bool Location::hasCompleteSet() const {
    if (_owner == nullptr) return false;

    for (const auto& loc : _sameColorLocations) {
        if (loc->getOwner() != _owner) {
            return false;
        }
    }
    return true;
}

int Location::getMinHouseCountInSet() const {
    int minHouseCount = 0x7fffffff;
    for (const auto& loc : _sameColorLocations) {
        if (loc->getHouseCount() < minHouseCount) {
            minHouseCount = loc->getHouseCount();
        }
    }
    return minHouseCount;
}



