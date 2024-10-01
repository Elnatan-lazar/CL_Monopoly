#include <algorithm>
#include "maingame.hpp"
#include "vector"
#include "playerManu.hpp"
#include "Card.hpp"
#include "action.hpp"
#include <thread>  // Include for sleep_for
#include <chrono>  // Include for chrono literals

using namespace std;

void ShowRules( sf::RenderWindow &window, sf::Font &font) {
    window.clear(sf::Color(50, 100, 150));
    // Create text objects for the rules
    sf::Text title("Game Rules", font, 30);
    title.setFillColor(sf::Color::White);
    title.setPosition(300, 20);

    sf::Text rulesPart1(
            "OBJECTIVE OF THE GAME\n"
            "Become the wealthiest player through buying, renting and selling of property and force other players into bankruptcy.\nthe first to reach 4000$ is the winner.\n\n"
            "GAMEPLAY\n"
            "At the start, each player throws the dice. The player with the highest total starts the play.\n"
            "All players start at \"START\" and are given the opportunity roll the two dice.\n"
            "Based on the total of the two, the player moves to a location and can buy the property, \nor pay rent/tax, draw a Chance/Community Chest card, Go To Jail, or etc...\n"
            "If the player throws doubles, they move their token and are subject to any privileges or penalties pertaining to the space on which they land.\n"
            "Then they can throw again and move their token as before. \nHowever, if the player ever throws doubles three times in succession, they are immediately sent to jail.\n",
            font, 20);
    rulesPart1.setFillColor(sf::Color::White);
    rulesPart1.setPosition(25, 80);

    sf::Text rulesPart2(
            "START\n"
            "Each time a player passes over START the player is paid a $200 salary.\n\n"
            "BUYING PROPERTY\n"
            "When a player lands on an unowned property they can buy that property at its printed price.\n\n"
            "PAYING RENT\n"
            "When a player lands on a property owned by another player, the owner collects rent in accordance with factors like no. of houses, hotels, etc.\n\n"
            "CHANCE AND COMMUNITY CHEST\n"
            "When a player lands here, they can receive a certain amount, have to pay a certain amount, or teleport to a random location.\n\n"
            "JAIL\n"
            "A player can be sent to jail when they land on \"GO TO JAIL\" or roll a certain number of doubles.\n"
            "The player is given the option to pay a certain amount to get out or can stay for a certain number of turns.\n"
            "If the player stays, at each turn, the number of turns to wait is displayed. The player cannot sell properties or buy houses/hotels when in jail.\n\n"
            "FREE PARKING\n"
            "Just a free location with no reward or penalty.\n\n"
            "HOUSES AND HOTELS\n"
            "If the player has completed a set, they are now allowed to buy a max of 4 Houses or a hotel if they have a sufficient balance.\n"
            "The player can build houses in only property type locations whose sets are completed.\n"
            "The player can only build a hotel if 4 houses have been built.\n\n"
            "BANKRUPTCY\n"
            "When the player has an amount lesser than 0 in hand, they are bankrupt and out. Players can sell properties to avoid so.\n",
            font, 20);
    rulesPart2.setFillColor(sf::Color::White);
    rulesPart2.setPosition(25, 80);

    // Button initialization
    sf::RectangleShape nextButton(sf::Vector2f(200, 50));
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));

    sf::Text nextText = createButtons(font, nextButton, 600, 1000, "Next", sf::Color::Green);
    sf::Text exitText = createButtons(font, exitButton, 300, 1000, "Exit", sf::Color::Red);

    // Variable to track which part of the rules we are on
    bool isSecondPart = false;

    // Main loop to display the rules
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            // Check for mouse button press
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    // Check if "Next" or "Previous" button is clicked
                    if (nextButton.getGlobalBounds().contains(mousePos)) {
                        if (!isSecondPart) {
                            // Move to the second part
                            isSecondPart = true;
                            nextText.setString("Previous"); // Change button to "Previous"
                        } else {
                            // Move back to the first part
                            isSecondPart = false;
                            nextText.setString("Next"); // Change button back to "Next"
                        }
                    }

                    // Check if "Exit" button is clicked
                    if (exitButton.getGlobalBounds().contains(mousePos)) {
                        return; // Exit the function
                    }
                }
            }
        }

        // Clear the window and draw the current part of the rules
        window.clear(sf::Color::Black);
        window.draw(title);
        if (isSecondPart) {
            window.draw(rulesPart2);
        } else {
            window.draw(rulesPart1);
        }

        // Draw buttons
        window.draw(nextButton);
        window.draw(nextText);
        window.draw(exitButton);
        window.draw(exitText);

        // Display the updated content
        window.display();
    }
}







void mainGame(sf::RenderWindow &window, sf::Font &font) {
    // Set up the board and players
    Board gameBoard;
    const int sidebarWidth = window.getSize().x / 4;

    // Sidebar
    sf::RectangleShape sidebar(sf::Vector2f(sidebarWidth, static_cast<float>(window.getSize().y)));
    sidebar.setPosition(static_cast<float>(window.getSize().x - sidebarWidth), 0);
    sidebar.setFillColor(sf::Color(50, 50, 50));

    // Read player information
    std::vector<Player> players;
    ReadPlayers(window, font, players);
    int currentPlayerIndex = SetPlayerOrder(window, font, players) - 1;
    for (Player &player : players) {
        player.setCurrentLocation(gameBoard.getLocations()[0]);
    }
    gameBoard.getLocations()[1]->setOwner(&players[0]);
    gameBoard.getLocations()[3]->setOwner(&players[0]);

    Location* location = gameBoard.getLocations()[1].get();
    Location* location2 = gameBoard.getLocations()[3].get();
//    location->buyHouse();
//    location2->buyHouse();
//    location->buyHouse();
//    location2->buyHouse();
//    location->buyHouse();
//    location2->buyHouse();
//    location->buyHouse();
//    location2->buyHouse();
    gameBoard.drawPlayerMarkers(window, players);

    // Button and Text Initialization
    sf::RectangleShape showPropertiesButton(sf::Vector2f(250, 50));
    sf::Text showPropertiesText = createText(font, "Show Properties", 20, sf::Color::White, sidebar.getPosition().x + 50, 210);
    showPropertiesButton.setPosition(sidebar.getPosition().x + 50, 210);
    showPropertiesButton.setFillColor(sf::Color::Blue);

    sf::RectangleShape rollDiceButton(sf::Vector2f(250, 50));
    sf::Text rollDiceText = createText(font, "Roll Dice", 20, sf::Color::White, sidebar.getPosition().x + 50, 270);
    rollDiceButton.setPosition(sidebar.getPosition().x + 50, 270);
    rollDiceButton.setFillColor(sf::Color::Green);

    sf::RectangleShape buyHouseButton(sf::Vector2f(250, 50));
    sf::Text buyHouseText = createText(font, "Buy House/Hotel", 20, sf::Color::White, sidebar.getPosition().x + 50, 330);
    buyHouseButton.setPosition(sidebar.getPosition().x + 50, 330);
    buyHouseButton.setFillColor(sf::Color::Cyan);

    sf::RectangleShape endTurnButton(sf::Vector2f(250, 50));
    sf::Text endTurnText = createText(font, "End Turn", 20, sf::Color::White, sidebar.getPosition().x + 50, 390);
    endTurnButton.setPosition(sidebar.getPosition().x + 50, 390);
    endTurnButton.setFillColor(sf::Color::Red);

    sf::RectangleShape sellButton(sf::Vector2f(250, 50));
    sf::Text sellButtonText = createText(font, "Sell", 20, sf::Color::White, sidebar.getPosition().x + 50, 450);
    sellButton.setPosition(sidebar.getPosition().x + 50, 450);
    sellButton.setFillColor(sf::Color::Magenta);

    sf::RectangleShape exitButton(sf::Vector2f(250, 50));
    sf::Text exitButtonText = createText(font, "exit", 20, sf::Color::Red, sidebar.getPosition().x + 50, 720);
    exitButton.setPosition(sidebar.getPosition().x + 50, 720);
    exitButton.setFillColor(sf::Color::Black);
    // Variables to track dice rolls and doubles
    bool hasRolledDice = false;
    int doubleRollCount = 0;  // Track consecutive doubles
    std::string rollResultMessage = " ";  // To display the dice result message
    int postion=players.size();
    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check for mouse click events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                // Handle the Roll Dice action
                if (!players[currentPlayerIndex].inJail() ) {
                    if (rollDiceButton.getGlobalBounds().contains(mousePos)&&!hasRolledDice) {
                        Dice dice;
                        dice.roll();
                        hasRolledDice = true;

                        // Create the roll result message
                        if (dice.isDouble()) {

                            doubleRollCount++;
                            rollResultMessage = "Double (" + std::to_string(dice.getDie1()) + ", " + std::to_string(dice.getDie2()) + ")! Roll again!";
                        } else {
                            doubleRollCount = 0;  // Reset the count if not a double
                            rollResultMessage = "You rolled (" + std::to_string(dice.getDie1()) + ", " + std::to_string(dice.getDie2()) + ")";
                        }

                        // Display the roll result message before any other action
                        window.clear(sf::Color(169, 169, 169));
                        gameBoard.draw(window);
                        gameBoard.drawPlayerMarkers(window, players);

                        // Draw the sidebar
                        window.draw(sidebar);
                        window.draw(showPropertiesButton);
                        window.draw(showPropertiesText);
                        window.draw(rollDiceButton);
                        window.draw(rollDiceText);
                        window.draw(buyHouseButton);
                        window.draw(buyHouseText);
                        window.draw(endTurnButton);
                        window.draw(endTurnText);

                        // Display other player information
                        window.draw(createText(font, "Player Turn: " + players[currentPlayerIndex].getName(), 24, sf::Color::White, sidebar.getPosition().x + 20, 20));
                        window.draw(createText(font, "Money: " + std::to_string(players[currentPlayerIndex].getCashInHand()), 20, sf::Color::White, sidebar.getPosition().x + 20, 80));
                        window.draw(createText(font, "Net Worth: " + std::to_string(players[currentPlayerIndex].getNetWorth()), 20, sf::Color::White, sidebar.getPosition().x + 20, 120));
                        window.draw(createText(font, "Get Out of Jail Cards: " + std::to_string(players[currentPlayerIndex].getOutOfJailCards()), 20, sf::Color::White, sidebar.getPosition().x + 20, 160));

                        // Display the roll result message
                        sf::Text rollResultText;
                        rollResultText.setFont(font);
                        rollResultText.setString(rollResultMessage);
                        rollResultText.setCharacterSize(20);
                        rollResultText.setFillColor(sf::Color::White);
                        rollResultText.setPosition(sidebar.getPosition().x + 20, sidebar.getPosition().y + sidebar.getSize().y - 50);
                        window.draw(rollResultText);

                        window.display();
                        //td::this_thread::sleep_for(std::chrono::seconds(2)); // Wait for 2 seconds before proceeding

                        // If the player rolled three doubles, send them to jail
                        if (doubleRollCount == 3) {
                            rollResultMessage = "3 doubles, go to jail!";
                            players[currentPlayerIndex].setInJail(true);
                            players[currentPlayerIndex].setJailTurn(3);
                            players[currentPlayerIndex].setCurrentLocation(gameBoard.getLocations()[10]);  // Move to jail location
                            gameBoard.drawPlayerMarkers(window, players);
                            doubleRollCount = 0;  // Reset the double count
                            hasRolledDice = true;  // End turn after going to jail
                        } else {
                            players[currentPlayerIndex].move(dice.getRoll(), gameBoard);
                            handleLandingAction(players[currentPlayerIndex], gameBoard, window, font, dice, players);
                            gameBoard.drawPlayerMarkers(window, players);

                            // Allow rolling again if it's a double
                            if (!dice.isDouble()) {
                                hasRolledDice = true;
                            } else {
                                hasRolledDice = false;
                            }
                        }
                    }
                    if (sellButton.getGlobalBounds().contains(mousePos)) {
                        sellMenu(players[currentPlayerIndex], window, font, gameBoard, players);
                    }
                    if (buyHouseButton.getGlobalBounds().contains(mousePos)) {
                        buyHouse(players[currentPlayerIndex], window, font);
                    }

                }
                else{
                    showJailMenu(players[currentPlayerIndex], window, font);
                    if(players[currentPlayerIndex].inJail()== false){
                        hasRolledDice = false;
                        rollResultMessage = " ";  // Clear the roll result message for the next player
                    } else{
                        players[currentPlayerIndex].setJailTurn(players[currentPlayerIndex].getJailTurn()-1);
                        if (players[currentPlayerIndex].getJailTurn()==0){
                            players[currentPlayerIndex].setInJail(false);
                            players[currentPlayerIndex].setCurrentLocation(gameBoard.getLocations()[10]);
                            gameBoard.drawPlayerMarkers(window, players);
                            hasRolledDice = true;
                            rollResultMessage = " ";  // Clear the roll result message for the next player
                        }

                    }
                }

                // Handle the End Turn action
                if (endTurnButton.getGlobalBounds().contains(mousePos)) {
                    if (!hasRolledDice) {
                        players[currentPlayerIndex].setTempMessage("You must roll dice before ending turn");
                    } else {
                        players[currentPlayerIndex].setTempMessage("");
                        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
                        while (players[currentPlayerIndex].isBankrupct()) {
                            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
                        }
                        hasRolledDice = false;
                        rollResultMessage = " ";  // Clear the roll result message for the next player
                    }
                }

                if (showPropertiesButton.getGlobalBounds().contains(mousePos)) {
                    showPropertiesWindow(players[currentPlayerIndex], font);
                }
                if (exitButton.getGlobalBounds().contains(mousePos)) {

                    return;
                }
            }
        }

        // Clear the window before drawing
        window.clear(sf::Color(169, 169, 169));

        // Draw the game board and player markers
        gameBoard.draw(window);
        gameBoard.drawPlayerMarkers(window, players);

        // Draw the sidebar and its components
        window.draw(sidebar);
        window.draw(createText(font, "Player Turn: " + players[currentPlayerIndex].getName(), 24, sf::Color::White, sidebar.getPosition().x + 20, 20));
        window.draw(createText(font, "Money: " + std::to_string(players[currentPlayerIndex].getCashInHand()), 20, sf::Color::White, sidebar.getPosition().x + 20, 80));
        window.draw(createText(font, "Net Worth: " + std::to_string(players[currentPlayerIndex].getNetWorth()), 20, sf::Color::White, sidebar.getPosition().x + 20, 120));
        window.draw(createText(font, "Get Out of Jail Cards: " + std::to_string(players[currentPlayerIndex].getOutOfJailCards()), 20, sf::Color::White, sidebar.getPosition().x + 20, 160));
        window.draw(showPropertiesButton);
        window.draw(showPropertiesText);
        window.draw(rollDiceButton);
        window.draw(rollDiceText);
        window.draw(buyHouseButton);
        window.draw(buyHouseText);
        window.draw(endTurnButton);
        window.draw(endTurnText);
        window.draw(sellButton);
        window.draw(sellButtonText);
        window.draw(exitButton);
        window.draw(exitButtonText);


        // Display the roll result message
        if (!rollResultMessage.empty()) {
            sf::Text rollResultText;
            rollResultText.setFont(font);
            rollResultText.setString(rollResultMessage);
            rollResultText.setCharacterSize(20);
            rollResultText.setFillColor(sf::Color::White);
            rollResultText.setPosition(sidebar.getPosition().x + 20, sidebar.getPosition().y + sidebar.getSize().y - 50);
            window.draw(rollResultText);
        }

        // Display the temporary message
        if (!players[currentPlayerIndex].getTempMessage().empty()) {
            sf::Text tempMessageText;
            tempMessageText.setFont(font);
            tempMessageText.setString(players[currentPlayerIndex].getTempMessage());
            tempMessageText.setCharacterSize(18);
            tempMessageText.setFillColor(sf::Color::Yellow);
            sf::FloatRect textRect = tempMessageText.getLocalBounds();
            tempMessageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            tempMessageText.setPosition(window.getSize().x / 2.0f - 200, window.getSize().y - 500);
            window.draw(tempMessageText);
        }

        // Display all elements
        window.display();
        if(players[currentPlayerIndex].isBankrupct()){
            players[currentPlayerIndex].setPosition(postion--);//update the  position of the player
            players[currentPlayerIndex].setTempMessage("");
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
            while (players[currentPlayerIndex].isBankrupct()) {
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
            }
        }
        if (checkAndDisplayWinner(players, window, font)) { // if there is a winner finish the game
            return ;
        }
    }
}

void showPropertiesWindow(Player &player, sf::Font &font) {
    // Create a new window for displaying properties
    sf::RenderWindow propertiesWindow(sf::VideoMode(600, 600), "Player Properties", sf::Style::Titlebar | sf::Style::Close);

    // Set up the exit button
    sf::RectangleShape exitButton(sf::Vector2f(100, 40));
    exitButton.setPosition(250, 520); // Center the button horizontally at the bottom
    exitButton.setFillColor(sf::Color::Red);

    // Set up the exit button text
    sf::Text exitButtonText;
    exitButtonText.setFont(font);
    exitButtonText.setString("Exit");
    exitButtonText.setCharacterSize(20);
    exitButtonText.setFillColor(sf::Color::White);
    sf::FloatRect exitTextRect = exitButtonText.getLocalBounds();
    exitButtonText.setOrigin(exitTextRect.left + exitTextRect.width / 2.0f, exitTextRect.top + exitTextRect.height / 2.0f);
    exitButtonText.setPosition(exitButton.getPosition().x + exitButton.getSize().x / 2, exitButton.getPosition().y + exitButton.getSize().y / 2);

    // Collect all properties into a single string
    std::string propertiesText;
    for (const std::shared_ptr<Location> &property : player.getPropertiesOwned()) {
        propertiesText += property->getName() + " - $" + std::to_string(property->getCost()) + "\n";
    }

    // Set up the properties text display
    sf::Text propertiesDisplayText;
    propertiesDisplayText.setFont(font);
    propertiesDisplayText.setString(propertiesText.empty() ? "No properties owned" : propertiesText);
    propertiesDisplayText.setCharacterSize(16);
    propertiesDisplayText.setFillColor(sf::Color::Black);
    propertiesDisplayText.setPosition(20, 20); // Set position with some padding

    // Main loop for the properties window
    while (propertiesWindow.isOpen()) {
        sf::Event event;
        while (propertiesWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                propertiesWindow.close();
            }

            // Check for mouse click events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = propertiesWindow.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                // Check if the exit button is clicked
                if (exitButton.getGlobalBounds().contains(mousePos)) {
                    propertiesWindow.close();
                }
            }
        }

        // Clear and draw everything in the properties window
        propertiesWindow.clear(sf::Color::White);
        propertiesWindow.draw(propertiesDisplayText);
        propertiesWindow.draw(exitButton);
        propertiesWindow.draw(exitButtonText);
        propertiesWindow.display();
    }
}



void buyHouse(Player &currentPlayer, sf::RenderWindow &window, sf::Font &font) {
    // Filter properties that belong to complete sets and are owned by the current player
    std::vector<std::shared_ptr<Location>> eligibleProperties;
    for (auto &property : currentPlayer.getPropertiesOwned()) {
        if (property->getType() == PROPERTY && currentPlayer.ownsCompleteSet(property->getColor())) {
            eligibleProperties.push_back(property);
        }
    }

    if (eligibleProperties.empty()) {
        // Display message if no eligible properties
        sf::Text noPropertiesText("No eligible properties to build on.", font, 24);
        noPropertiesText.setFillColor(sf::Color::Red);
        noPropertiesText.setPosition((window.getSize().x - noPropertiesText.getGlobalBounds().width) / 2, (window.getSize().y - noPropertiesText.getGlobalBounds().height) / 2);
        window.clear();
        window.draw(noPropertiesText);
        window.display();
        sf::sleep(sf::seconds(2)); // Display the message for 2 seconds
        return;
    }

    // Create an overlay for the menu
    sf::RectangleShape overlay(sf::Vector2f(800, 600));
    overlay.setFillColor(sf::Color(255, 255, 255, 200)); // Semi-transparent white background
    overlay.setPosition((window.getSize().x - 800) / 2, (window.getSize().y - 600) / 2);

    // Display property list
    std::vector<sf::Text> propertyTexts;
    for (size_t i = 0; i < eligibleProperties.size(); ++i) {
        sf::Text propText = createText(font, eligibleProperties[i]->getName() + " - $" + std::to_string(eligibleProperties[i]->getCost()), 20, sf::Color::Black, overlay.getPosition().x + 20, overlay.getPosition().y + 50 + static_cast<float>(i) * 30);
        propertyTexts.push_back(propText);
    }

    // Create Exit Button
    sf::RectangleShape exitButton(sf::Vector2f(150, 40));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(overlay.getPosition().x + 620, overlay.getPosition().y + 520);

    sf::Text exitButtonText("Exit", font, 20);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setPosition(exitButton.getPosition().x + (exitButton.getSize().x - exitButtonText.getGlobalBounds().width) / 2, exitButton.getPosition().y + 5);

    // Create the buy house/hotel and cancel buttons
    sf::RectangleShape buyHouseButton(sf::Vector2f(150, 40));
    sf::RectangleShape buyHotelButton(sf::Vector2f(150, 40));
    sf::RectangleShape cancelButton(sf::Vector2f(150, 40));

    sf::Text buyHouseText("Buy House", font, 20);
    sf::Text buyHotelText("Buy Hotel", font, 20);
    sf::Text cancelText("Cancel", font, 20);

    bool selectingProperty = true;
    int selectedIndex = -1;

    // Main loop for the buy menu
    while (window.isOpen() && selectingProperty) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                // Check if the exit button is clicked
                if (exitButton.getGlobalBounds().contains(mousePos)) {
                    window.clear();
                    return;
                }

                // Check if a property was clicked
                for (size_t i = 0; i < propertyTexts.size(); ++i) {
                    if (propertyTexts[i].getGlobalBounds().contains(mousePos)) {
                        selectedIndex = i;
                        selectingProperty = false;

                        // Set up buttons for buying house/hotel
                        buyHouseButton.setPosition(overlay.getPosition().x + 20, overlay.getPosition().y + 500);
                        buyHotelButton.setPosition(overlay.getPosition().x + 200, overlay.getPosition().y + 500);
                        cancelButton.setPosition(overlay.getPosition().x + 380, overlay.getPosition().y + 500);

                        buyHouseButton.setFillColor(sf::Color::Green);
                        buyHotelButton.setFillColor(sf::Color::Blue);
                        cancelButton.setFillColor(sf::Color::Yellow);

                        buyHouseText.setPosition(buyHouseButton.getPosition().x + 20, buyHouseButton.getPosition().y + 5);
                        buyHotelText.setPosition(buyHotelButton.getPosition().x + 20, buyHotelButton.getPosition().y + 5);
                        cancelText.setPosition(cancelButton.getPosition().x + 20, cancelButton.getPosition().y + 5);
                    }
                }

                // Check if the cancel button is clicked
                if (selectedIndex != -1 && cancelButton.getGlobalBounds().contains(mousePos)) {
                    selectingProperty = true;
                    selectedIndex = -1; // Deselect property
                }

                // Check if the buy house button is clicked
                if (selectedIndex != -1 && buyHouseButton.getGlobalBounds().contains(mousePos)) {
                    if (eligibleProperties[selectedIndex]->canBuildHouse() && currentPlayer.getCashInHand() >= eligibleProperties[selectedIndex]->getHouseCost()) {
                        eligibleProperties[selectedIndex]->buyHouse();
                        currentPlayer.updateCashInHand(-eligibleProperties[selectedIndex]->getHouseCost());
                        currentPlayer.setTempMessage("House bought for " + eligibleProperties[selectedIndex]->getName());
                    } else {
                        currentPlayer.setTempMessage("Cannot build a house here.");
                    }
                    return;
                }

                // Check if the buy hotel button is clicked
                if (selectedIndex != -1 && buyHotelButton.getGlobalBounds().contains(mousePos)) {
                    if (eligibleProperties[selectedIndex]->canBuildHotel() && currentPlayer.getCashInHand() >= eligibleProperties[selectedIndex]->getHotelCost()) {
                        eligibleProperties[selectedIndex]->buyHotel();
                        currentPlayer.updateCashInHand(-eligibleProperties[selectedIndex]->getHotelCost());
                        currentPlayer.setTempMessage("Hotel bought for " + eligibleProperties[selectedIndex]->getName());
                    } else {
                        currentPlayer.setTempMessage("Cannot build a hotel here.");
                    }
                    return;
                }
            }
        }

        // Draw the menu
        window.clear(sf::Color(169, 169, 169));
        window.draw(overlay);

        for (auto &text : propertyTexts) {
            window.draw(text);
        }

        // Draw buttons
        window.draw(exitButton);
        window.draw(exitButtonText);

        if (selectedIndex != -1) {
            window.draw(buyHouseButton);
            window.draw(buyHouseText);
            window.draw(buyHotelButton);
            window.draw(buyHotelText);
            window.draw(cancelButton);
            window.draw(cancelText);
        }

        window.display();
    }
}






