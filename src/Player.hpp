#ifndef CL_MONOPOLY_PLAYER_HPP
#define CL_MONOPOLY_PLAYER_HPP

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Location.hpp"
#include "Board.hpp"

class Player : public std::enable_shared_from_this<Player> {
private:
    int ID;                        // Unique identifier for the player
    std::string name;              // Player's name
    sf::Color color;               // Player's color
    int netWorth;                  // Player's total net worth
    int cashInHand;                // Player's cash balance
    bool bankrupt;                   // Status if the player is out of the game
    bool isBankrupt;               // Status if the player is bankrupt
    bool isInJail;                 // Status if the player is in jail
    int jailTurn;                  // Remaining turns in jail
    int propertyOwnedCount;        // Total number of properties owned by the player
    std::vector<std::shared_ptr<Location>> propertiesOwned; // Properties owned by the player
    int position;                  // Current position on the board
    int outOfJailCards;            // Number of Get Out of Jail Free cards
    std::shared_ptr<Location> currentLocation; // Current board location of the player
    std::string tempMessage;
public:
    // Constructors and Destructor
    Player();
    Player(const std::string &name);
    Player(const Player& other);  // Copy constructor
    ~Player();

    // Getters and Setters
    int getID() const;
    void setID(int id);
    std::string getName() const;
    void setName(const std::string &new_name);
    int getNetWorth() const;
    void updateNetWorth(int amount);
    int getCashInHand() const;
    void updateCashInHand(int amount);
    sf::Color getColor() const;
    void setColor(sf::Color c);
    bool isBankrupct() const;
    void setBankrupct();
    bool inJail() const;
    void setInJail(bool jailStatus);
    int getJailTurn() const;
    void setJailTurn(int num);
    void addOutOfJailCard();
    int getOutOfJailCards() const;
    void useGetOutOfJailCard();
    std::shared_ptr<Location> getCurrentLocation() const;
    void setCurrentLocation(std::shared_ptr<Location> newLocation);

    // Property management
    void addProperty(std::shared_ptr<Location> loc);
    void removeProperty(std::shared_ptr<Location> location);
    const std::vector<std::shared_ptr<Location>>& getPropertiesOwned() const;
    bool ownsCompleteSet(sf::Color color) const;  // Check if the player owns a complete set of a color
    void resetProperties();



    void setPosition(int pos);

    void move(int i, Board &board);
    void setTempMessage(const std::string& message);

    std::string getTempMessage() const ;
    void clearTempMessage();

    void clearProperties();
};

#endif //CL_MONOPOLY_PLAYER_HPP
