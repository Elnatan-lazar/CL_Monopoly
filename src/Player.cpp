#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include "Location.hpp"

// Constructors
Player::Player()
        : netWorth(1500), color(sf::Color::White), cashInHand(1500), bankrupt(false),
          isBankrupt(false), isInJail(false), jailTurn(0), propertyOwnedCount(0),
          position(0), outOfJailCards(0), currentLocation(nullptr) {}

Player::Player(const std::string &new_name)
        : name(new_name), netWorth(1500), color(sf::Color::White), cashInHand(1500),
          bankrupt(false), isBankrupt(false), isInJail(false), jailTurn(0),
          propertyOwnedCount(0), position(0), outOfJailCards(0), currentLocation(nullptr) {}

Player::Player(const Player& other)
        : ID(other.ID), name(other.name), color(other.color), netWorth(other.netWorth),
          cashInHand(other.cashInHand), bankrupt(other.bankrupt), isBankrupt(other.isBankrupt),
          isInJail(other.isInJail), jailTurn(other.jailTurn), propertyOwnedCount(other.propertyOwnedCount),
          position(other.position), outOfJailCards(other.outOfJailCards), propertiesOwned(other.propertiesOwned) {
    if (other.currentLocation) {
        currentLocation = std::make_shared<Location>(*other.currentLocation);
    }
}

Player::~Player() {
    propertiesOwned.clear();
}

// Getter and setter methods
int Player::getID() const { return ID; }
void Player::setID(int id) { ID = id; }
std::string Player::getName() const { return name; }
void Player::setName(const std::string &new_name) { name = new_name; }
int Player::getNetWorth() const { return netWorth; }
void Player::updateNetWorth(int amount) { netWorth += amount; }
int Player::getCashInHand() const { return cashInHand; }
void Player::updateCashInHand(int amount) {
    cashInHand += amount;
}
sf::Color Player::getColor() const { return color; }
void Player::setColor(sf::Color c) { color = c; }
bool Player::isBankrupct() const { return bankrupt; }
void Player::setBankrupct() { bankrupt = true; }
bool Player::inJail() const { return isInJail; }
void Player::setInJail(bool jailStatus) { isInJail = jailStatus; }
int Player::getJailTurn() const { return jailTurn; }
void Player::setJailTurn(int num) { jailTurn = num; }
void Player::addOutOfJailCard() { outOfJailCards++; }
int Player::getOutOfJailCards() const { return outOfJailCards; }
void Player::useGetOutOfJailCard() { if (outOfJailCards > 0) outOfJailCards--; }

std::shared_ptr<Location> Player::getCurrentLocation() const { return currentLocation; }
void Player::setCurrentLocation(std::shared_ptr<Location> newLocation) { currentLocation = newLocation; }

// Property management methods
void Player::addProperty(std::shared_ptr<Location> loc) {
    propertiesOwned.push_back(loc);
    loc->setOwner(this);
}

void Player::removeProperty(std::shared_ptr<Location> location) {
    auto it = std::find_if(propertiesOwned.begin(), propertiesOwned.end(),
                           [&](const std::shared_ptr<Location>& loc) { return loc->getID() == location->getID(); });

    if (it != propertiesOwned.end()) {
        (*it)->setOwner(nullptr); // Reset the owner of the property
        propertiesOwned.erase(it);
    }
}

const std::vector<std::shared_ptr<Location>>& Player::getPropertiesOwned() const {
    return propertiesOwned;
}

bool Player::ownsCompleteSet(sf::Color color) const {
    // Check if the player owns all properties of the specified color
    for (const auto& property : propertiesOwned) {
        if (property->getColor() == color && !property->hasCompleteSet()) {
            return false;
        }
    }
    return true;
}

void Player::resetProperties() {
    for (auto& property : propertiesOwned) {
        property->reset();
    }
    propertiesOwned.clear();
}



// Position methods
void Player::setPosition(int pos) { position = pos; }

void Player::move(int i, Board &board) {
    int totalLocations = board.getLocations().size(); // Total locations on the board
    int currentPos = currentLocation->getID() - 1; // Get the current position (0-based index)
    int newPosition = (currentPos + i) % totalLocations; // Calculate the new position

    // Check if the player will pass "Start"
    if (currentPos + i >= totalLocations) {
        if (newPosition == 0) {
            updateCashInHand(400); // Player landed on Start, so collect $400
            std::cout << getName() << " landed on Start and collects $400!" << std::endl;
            setTempMessage(getName() + " landed on Start and collects $400!");
        } else {
            updateCashInHand(200); // Player passed "Start," so collect $200
            std::cout << getName() << " passed Start and collects $200!" << std::endl;
            setTempMessage(getName() + " passed Start and collects $200!");
        }
    }

    // Update the current location to the new one
    currentLocation = board.getLocations()[newPosition];
}


void Player::setTempMessage(const std::string& message) {
    tempMessage = message;
}

std::string Player::getTempMessage() const {
    return tempMessage;
}

void Player::clearTempMessage() {
    tempMessage.clear();
}
void Player::clearProperties() {
    propertiesOwned.clear();
}