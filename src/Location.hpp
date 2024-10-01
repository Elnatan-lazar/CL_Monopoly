#ifndef CL_MONOPOLY_LOCATION_HPP
#define CL_MONOPOLY_LOCATION_HPP

#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include <vector>

class Player;

class Location {
private:
    int _cost;
    int _id;
    std::string _name;
    int _houseCount = 0;
    bool _hasHotel = false;
    int _hotelCost;
    int _houseCost;
    int _baseRent;
    int _hotelRent;
    sf::Color _color;
    LocType _type;
   Player* _owner = nullptr;
    std::vector<std::shared_ptr<Location>> _sameColorLocations;  // Locations with the same color (for complete set check)

public:
    Location();
    Location(int id, LocType type, const std::string &name, sf::Color color);
    Location(int id, LocType type, const std::string &name, sf::Color color,int rent);
    Location(int id, LocType type, const std::string &name, sf::Color color, int cost, int rent);
    Location(int id, LocType type, const std::string &name, sf::Color color, int cost, int baseRent, int buildCost, int hotelRent, int hotelCost);

    int getCost() const;
    int getID() const;
    std::string getName() const;
    int getRent() const;
    int getHotelCost() const;
    int getHouseCost() const;
    int getHouseCount() const;
    sf::Color getColor() const;
    bool hasHotel() const;
    Player *const getOwner() const;
    LocType getType() const;

    void setID(int id);
    void setName(const std::string &new_name);
    void setOwner(Player* player);
    void setColour(sf::Color new_colour);

    bool buyHotel();
    bool buyHouse();
    void reset();

    // New methods
    bool canBuildHouse();
    bool canBuildHotel();
    void addSameColorLocation(std::shared_ptr<Location> location);
    bool hasCompleteSet() const;
    int getMinHouseCountInSet() const;


};

#endif //CL_MONOPOLY_LOCATION_HPP
