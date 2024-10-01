#include "Card.hpp"


    Card::Card(CardType cardType, unsigned int money, unsigned int locationID, const std::string& desc)
            : type(cardType), money(money), locationID(locationID), description(desc) {}

    CardType Card::getType() const { return type; }
    unsigned int Card::getMoney() const { return money; }
    unsigned int Card::getLocationID() const { return locationID; }
    std::string Card::getDescription() const { return description; }

    void Card::displayCardInfo() const {
        std::cout << "Card Type: " << (type == BAD ? "Bad" : type == GOOD ? "Good" : "Neutral") << "\n"
                  << "Description: " << description << "\n";
        if (type != NEUTRAL) {
            std::cout << "Money: " << money << "\n";
        }
        if (locationID != 0) {
            std::cout << "Location ID: " << locationID << "\n";
        }
    }

    // Method to draw a random Chance card
    Card Card::drawChanceCard() {
        srand(time(0));
        int randChoice = rand() % 16;

        switch (randChoice) {
            case 0:
                return Card(GOOD, 200, 0, "Advance to Go (Collect $200)");
            case 1:
                return Card(GOOD, 50, 0, "Bank pays you dividend of $50");
            case 2:
                return Card(NEUTRAL, 0, -3, "Go back 3 spaces");
            case 3:
                return Card(NEUTRAL, 0, 10, "Go directly to Jail – do not pass Go, do not collect $200");
            case 4:
                return Card(BAD, 0, 0, "Make general repairs on all your property – For each house pay $25 – For each hotel $100");
            case 5:
                return Card(BAD, 15, 0, "Pay poor tax of $15");
            case 6:
                return Card(NEUTRAL, 200, 5, "Take a trip to Reading Railroad – If you pass Go collect $200");
            case 7:
                return Card(NEUTRAL, 0, 39, "Take a walk on the Boardwalk – Advance token to Boardwalk");
            case 8:
                return Card(BAD, 0, 0, "You have been elected Chairman of the Board – Pay each player $50");
            case 9:
                return Card(GOOD, 150, 0, "Your building loan matures – Collect $150");
            case 10:
                return Card(GOOD, 0, 0, "Get out of Jail Free – This card may be kept until needed or traded");
            case 11:
                return Card(NEUTRAL, 200, 24, "Advance to Illinois Ave. – If you pass Go, collect $200");
            case 12:
                return Card(NEUTRAL, 200, 11, "Advance to St. Charles Place – If you pass Go, collect $200");
            case 13:
                return Card(BAD, 0, 0, "You are assessed for street repairs – $40 per house, $115 per hotel");
            case 14:
                return Card(NEUTRAL, 0, 0, "Advance to nearest Utility – If unowned you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown.");
            case 15:
                return Card(NEUTRAL, 0, 0, "Advance to nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental to which they are otherwise entitled.");
            default:
                return Card(NEUTRAL, 0, 0, "No effect.");
        }
    }

    // Method to draw a random Community Chest card
    Card Card::drawCommunityCard() {
        srand(time(0));
        int randChoice = rand() % 5;

        switch (randChoice) {
            case 0:
                return Card(GOOD, 100, 0, "Bank error in your favor, collect $100!");
            case 1:
                return Card(BAD, 50, 0, "Doctor's fee, pay $50.");
            case 2:
                return Card(NEUTRAL, 0, 11, "Go to Jail! Move directly to jail.");
            case 3:
                return Card(GOOD, 200, 0, "You inherit $200.");
            case 4:
                return Card(BAD, 20, 0, "Pay $20 for street repairs.");
            default:
                return Card(NEUTRAL, 0, 0, "No effect.");
        }
    }

