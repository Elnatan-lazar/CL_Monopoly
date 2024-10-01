#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Dice.hpp"
#include "Location.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "definitions.hpp"

// Test for Player class
TEST_CASE("Player Class Tests") {
    Board board;

    SUBCASE("Check total number of locations") {
        CHECK(board.getLocations().size() == 40);
    }

    SUBCASE("Check specific location details") {
        auto goLocation = board.getLocations()[0];
        CHECK(goLocation->getName() == "START");
        CHECK(goLocation->getType() == FREE);
    }

    SUBCASE("Player position management") {
        Player player("Alice");
        player.setCurrentLocation(board.getLocations()[5]); // Set player position
        CHECK(player.getCurrentLocation()->getName() == board.getLocations()[5]->getName());
    }

    Player player("John");

    SUBCASE("Initial attributes") {
        CHECK(player.getName() == "John");
        CHECK(player.getID() == 1);
        CHECK(player.getCashInHand() == 1500);
        CHECK(player.getNetWorth() == 1500);
        CHECK(player.inJail() == false);
        CHECK(player.isBankrupct() == false);
    }

    SUBCASE("Updating player attributes") {
        player.updateCashInHand(-500);
        CHECK(player.getCashInHand() == 1000);
        player.updateNetWorth(1000);
        CHECK(player.getNetWorth() == 2500);
    }

    SUBCASE("Property management") {
        sf::Color color = sf::Color::Green;
        Location location1(1, PROPERTY, "Park Place", color, 350, 35, 200, 1750, 200);

        player.addProperty(std::make_shared<Location>(location1));
        CHECK(player.getPropertiesOwned().size() == 1);

        player.removeProperty(std::make_shared<Location>(location1));
        CHECK(player.getPropertiesOwned().size() == 0);
    }

    SUBCASE("Jail functionality") {
        player.setInJail(true);
        CHECK(player.inJail() == true);
        player.setInJail(false);
        CHECK(player.inJail() == false);
    }

    SUBCASE("Bankruptcy functionality") {
        player.setBankrupct();
        CHECK(player.isBankrupct() == true);
    }

    Player player1("Player1");
    sf::Color color = sf::Color::Blue;
    Location loc1(1, PROPERTY, "Baltic Avenue", color, 100, 10, 50, 250, 100);
    loc1.setOwner(&player1);

    SUBCASE("Verify getters") {
        CHECK(loc1.getID() == 1);
        CHECK(loc1.getName() == "Baltic Avenue");
        CHECK(loc1.getCost() == 100);
        CHECK(loc1.getHotelCost() == 100);
        CHECK(loc1.getHouseCost() == 50);
        CHECK(loc1.getRent() == 10);
        CHECK(loc1.getColor() == sf::Color::Blue);
        CHECK(loc1.getOwner() == &player1);
    }

    SUBCASE("Building houses and hotels") {
        // Test house building
        CHECK(loc1.buyHouse() == true);
        CHECK(loc1.getHouseCount() == 1);

        loc1.buyHouse();
        loc1.buyHouse();
        loc1.buyHouse();
        CHECK(loc1.getHouseCount() == 4);

        CHECK(loc1.buyHouse() == false); // Should not allow more than 4 houses

        // Test building a hotel
        CHECK(loc1.buyHotel() == true);
        CHECK(loc1.hasHotel() == true);

        // Reset location and check
        loc1.reset();
        CHECK(loc1.getHouseCount() == 0);
        CHECK(loc1.hasHotel() == false);
    }



    Dice dice;

    SUBCASE("Rolling the dice") {
        int rollValue = dice.roll();
        CHECK(rollValue >= 2); // Minimum sum of two dice (1+1)
        CHECK(rollValue <= 12); // Maximum sum of two dice (6+6)
    }

    SUBCASE("Checking double functionality") {
        int die1 = dice.getDie1();
        int die2 = dice.getDie2();
        if (die1 == die2) {
            CHECK(dice.isDouble() == true);
        } else {
            CHECK(dice.isDouble() == false);
        }
    }

    SUBCASE("Get individual dice values") {
        dice.roll();
        CHECK(dice.getDie1() >= 1);
        CHECK(dice.getDie1() <= 6);
        CHECK(dice.getDie2() >= 1);
        CHECK(dice.getDie2() <= 6);
        CHECK(dice.getRoll() == dice.getDie1() + dice.getDie2());
    }
}

