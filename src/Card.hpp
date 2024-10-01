#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "definitions.hpp"




    class Card {
    private:
        CardType type;
        unsigned int money;
        unsigned int locationID;
        std::string description;

    public:
        // Constructor
        Card(CardType cardType = NEUTRAL, unsigned int money = 0, unsigned int locationID = 0, const std::string& desc = "");

        // Getters and setters
        CardType getType() const;
        unsigned int getMoney() const;
        unsigned int getLocationID() const;
        std::string getDescription() const;

        // Static methods to draw random cards
        static Card drawChanceCard();
        static Card drawCommunityCard();

        // Display card information
        void displayCardInfo() const;
    };


#endif
