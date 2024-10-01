#include <algorithm>
#include <iomanip>
#include "playerManu.hpp"
#include "vector"
#include "Player.hpp"
#include  <array>



void showJailMenu(Player& currentPlayer, sf::RenderWindow& window, sf::Font& font) {
    // Create text and buttons
    sf::Text jailMenuText = createText(font, currentPlayer.getName() + ", you are in jail! Choose an option:", 24, sf::Color::White, 650, 20);

    sf::RectangleShape rollDiceButton;
    sf::Text rollDiceText;
    createButton(rollDiceButton, rollDiceText, font, "Roll Dice", 700, 200, sf::Color::Blue, sf::Color::White);

    sf::RectangleShape useCardButton;
    sf::Text useCardText;
    createButton(useCardButton, useCardText, font, "Use Get Out Card", 700, 300, sf::Color::Green, sf::Color::White);

    bool stayInJail = true;

    while (window.isOpen() && stayInJail) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                if (rollDiceButton.getGlobalBounds().contains(mousePos)) {
                    Dice dice;
                    dice.roll();
                    if (dice.isDouble()) {
                        currentPlayer.setInJail(false);
                        stayInJail = false;
                    } else {
                        currentPlayer.setJailTurn(currentPlayer.getJailTurn() - 1);
                        if (currentPlayer.getJailTurn() <= 0) {
                            currentPlayer.setInJail(false);
                            stayInJail = false;
                        }
                    }
                    return; //finish turn
                }
                if (useCardButton.getGlobalBounds().contains(mousePos) && currentPlayer.getOutOfJailCards() > 0) {
                    currentPlayer.useGetOutOfJailCard();
                    currentPlayer.setInJail(false);
                    stayInJail = false;
                    return; //finish turn
                }
            }
        }

        window.clear();
        window.draw(jailMenuText);
        window.draw(rollDiceButton);
        window.draw(rollDiceText);
        window.draw(useCardButton);
        window.draw(useCardText);
        window.display();
    }
}


using namespace std;
// Function to get a unique color for each player
sf::Color getPlayerColor(int playerIndex) {
    static std::array<sf::Color, 8> colors = {
            sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow,
            sf::Color::Magenta, sf::Color::Cyan, sf::Color::White, sf::Color(255, 165, 0) // Orange
    };
    return colors[playerIndex % colors.size()];
}


int ReadPlayers(sf::RenderWindow& window, sf::Font& font, std::vector<Player>& players) {
    std::string inp;
    int num = 0;
    bool validInput = false;

    sf::Text promptText;
    promptText.setFont(font);
    promptText.setCharacterSize(24);
    promptText.setFillColor(sf::Color::White);
    promptText.setPosition(50, 50);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setPosition(50, 100);

    promptText.setString("Enter the number of players (2-8) or X to exit:");

    // Input capture loop for the number of players
    while (window.isOpen() && !validInput) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return EXIT_FAILURE; // Handle window close
            }

            // Capture keyboard input
            if (event.type == sf::Event::TextEntered) {
                if (std::isdigit(event.text.unicode)) {
                    inp += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == 8 && !inp.empty()) { // Handle backspace
                    inp.pop_back();
                } else if (event.text.unicode == 'x' || event.text.unicode == 'X') {
                    exit(0);
                } else if (event.text.unicode == 13) { // Enter key
                    try {
                        num = std::stoi(inp);
                        if (num >= 2 && num <= 8) {
                            validInput = true;
                            break;
                        } else {
                            inp.clear();
                            promptText.setString("Invalid input. Enter a number from 2-8 or X to exit:");
                        }
                    } catch (std::invalid_argument&) {
                        inp.clear();
                        promptText.setString("Invalid input. Enter a number from 2-8 or X to exit:");
                    }
                }
            }
        }

        // Update the input text display
        inputText.setString(inp);

        // Clear and draw everything
        window.clear();
        window.draw(promptText);
        window.draw(inputText);
        window.display();
    }

    players.resize(num);

    // Now get player names and assign colors
    for (int i = 0; i < num; i++) {
        inp.clear();
        sf::Color playerColor = getPlayerColor(i);  // Get color for the player
        promptText.setString("Player " + std::to_string(i + 1) + " enter name:");
        inputText.setFillColor(playerColor);

        bool nameEntered = false;
        while (window.isOpen() && !nameEntered) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return EXIT_FAILURE; // Handle window close
                }

                // Capture keyboard input for the name
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 13) { // Enter key
                        players[i].setName(inp);
                        players[i].setID(i + 1);
                        players[i].setColor(playerColor); // Assuming you have a method to set the player's color
                        nameEntered = true;
                    } else if (event.text.unicode == 8 && !inp.empty()) { // Handle backspace
                        inp.pop_back();
                    } else if (event.text.unicode < 128 && event.text.unicode != 13 && event.text.unicode != 8) {
                        inp += static_cast<char>(event.text.unicode);
                    }
                }
            }

            // Update the display for the name input
            inputText.setString(inp);
            window.clear();
            window.draw(promptText);
            window.draw(inputText);
            window.display();
        }
    }

    // Display table of players with the "Next" button
    sf::RectangleShape nextButton(sf::Vector2f(200, 50));
    nextButton.setFillColor(sf::Color::Green);
    nextButton.setPosition(300, 500);
    sf::Text nextText = createText(font, "Next", 24, sf::Color::White, 340, 510);

    bool proceedToGame = false;
    while (window.isOpen() && !proceedToGame) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return EXIT_FAILURE;
            }

            // Check if the "Next" button was clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                if (nextButton.getGlobalBounds().contains(mousePos)) {
                    proceedToGame = true;
                }
            }
        }

        window.clear();
        // Display all player names with their respective colors
        for (int i = 0; i < num; i++) {
            sf::Text playerName = createText(font, to_string(i+1)+" - "+players[i].getName(), 24, getPlayerColor(i), 100, 50 + (i * 30));
            window.draw(playerName);
        }

        window.draw(nextButton);
        window.draw(nextText);
        window.display();
    }

    return EXIT_SUCCESS;
}


int SetPlayerOrder(sf::RenderWindow& window, sf::Font& font, std::vector<Player>& players) {
    Dice dice;
    int maxRoll = 0, count = 0, winnerID = 0;
    bool orderDetermined = false;
    int currentPlayerIndex = 0; // Index to keep track of the current player

    // Text for displaying information
    sf::Text statusText = createText(font, "Player order setup: Click 'Roll Dice' for each player.", 24, sf::Color::White, 50, 20);

    // Create the "Roll Dice" button
    sf::RectangleShape rollDiceButton;
    sf::Text rollDiceText;
    createButton(rollDiceButton, rollDiceText, font, "Roll Dice", 600, 400, sf::Color::Blue, sf::Color::White);

    // Create the "Next" button but it will be shown only after the order is determined
    sf::RectangleShape nextButton;
    sf::Text nextText;
    createButton(nextButton, nextText, font, "Next", 600, 500, sf::Color::Green, sf::Color::White);

    std::vector<int> rollResults(players.size(), 0); // Store each player's roll result (0 means not yet rolled)

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return EXIT_FAILURE;
            }

            // Check for button clicks
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                // Handle "Roll Dice" button click
                if (!orderDetermined && rollDiceButton.getGlobalBounds().contains(mousePos)) {
                    int totalRoll = dice.roll(); // Roll the dice for the current player
                    rollResults[currentPlayerIndex] = totalRoll;

                    std::string rollMessage = players[currentPlayerIndex].getName() + " rolled a " +
                                              std::to_string(dice.getDie1()) + " and a " +
                                              std::to_string(dice.getDie2()) + " for a total of " +
                                              std::to_string(totalRoll) + ".";
                    statusText.setString(rollMessage);

                    // Update max roll and check for ties
                    if (totalRoll > maxRoll) {
                        maxRoll = totalRoll;
                        count = 0;
                        winnerID = players[currentPlayerIndex].getID();
                    } else if (totalRoll == maxRoll) {
                        statusText.setString(rollMessage);
                        count++;
                    }

                    currentPlayerIndex++; // Move to the next player

                    if (currentPlayerIndex >= players.size()) {
                        // Check if there's a tie
                        if (count == 0) {
                            orderDetermined = true;
                            statusText.setString("Player order determined First palyer is player number "+ to_string(winnerID) +" . Click 'Next' to continue.");
                        } else {
                            statusText.setString("There was a tie. Click 'Roll Dice' again.");
                            currentPlayerIndex = 0;
                            maxRoll = 0;
                            count = 0;
                            winnerID = 0;
                            rollResults.assign(players.size(), 0); // Reset all player roll statuses
                        }
                    }
                }

                // Handle "Next" button click (only if the order is determined)
                if (orderDetermined && nextButton.getGlobalBounds().contains(mousePos)) {
                    return winnerID; // Return the ID of the player who rolled the highest
                }
            }
        }

        // Draw the UI elements
        window.clear();  // Clear the window before drawing
        window.draw(statusText);

        // Draw the roll button if the order is not determined yet
        if (!orderDetermined) {
            window.draw(rollDiceButton);
            window.draw(rollDiceText);
        }

        // Draw the "Next" button if the order is determined
        if (orderDetermined) {
            window.draw(nextButton);
            window.draw(nextText);
        }

        // Display the player rolls
        for (int i = 0; i < players.size(); ++i) {
            std::string rollMessage = players[i].getName() + ": ";
            if (rollResults[i] > 0) {
                rollMessage += std::to_string(rollResults[i]);
            } else {
                rollMessage += "Not rolled yet";
            }
            sf::Text playerRollText = createText(font, rollMessage, 20, players[i].getColor(), 50, 100 + (i * 30));
            window.draw(playerRollText);
        }

        // Display everything
        window.display();
    }

    return winnerID;
}




int RentCalc(Player* owner, std::shared_ptr<Location> currentLocation, Board& board, int roll) {
    // Check if the location type is RAIL
    if (currentLocation->getType() == RAIL) {
        int railsOwned = 0;

        // Iterate through all board locations to count the railroads owned by the player
        for (const auto& location : board.getLocations()) {
            if (location->getType() == RAIL && location->getOwner() != nullptr && location->getOwner()->getID() == owner->getID()) {
                railsOwned++;
            }
        }

        // Rent for railroads is calculated as 25 multiplied by the number of railroads owned
        return 25 * railsOwned;
    }
        // Check if the location type is UTILITY
    else if (currentLocation->getType() == UTILITY) {
        // Rent for utilities is calculated as 10 multiplied by the dice roll
        return 10 * roll;
    }

    // For other types, return the base rent
    return currentLocation->getRent();
}

void sellMenu(Player &player, sf::RenderWindow &window, sf::Font &font, Board& gameBoard, std::vector<Player>& players) {
    if (player.getPropertiesOwned().empty()) {
        // If the player has no properties to sell, show a message
        sf::Text noPropertiesText("You have no properties to sell.", font, 24);
        noPropertiesText.setFillColor(sf::Color::Red);
        noPropertiesText.setPosition((window.getSize().x - noPropertiesText.getGlobalBounds().width) / 2, (window.getSize().y - noPropertiesText.getGlobalBounds().height) / 2);


        gameBoard.draw(window);
        gameBoard.drawPlayerMarkers(window, players); // Redraw all player markers
        window.draw(noPropertiesText);
        window.display();
        sf::sleep(sf::seconds(2)); // Display the message for 2 seconds
        return;
    }

    // Create the overlay rectangle for the Sell Menu
    sf::RectangleShape overlay(sf::Vector2f(600, 400));
    overlay.setFillColor(sf::Color(255, 255, 255, 200)); // Semi-transparent white background
    overlay.setPosition((window.getSize().x - 1000) / 2, (window.getSize().y - 400) / 2); // Center the overlay

    // Set up the "Sell" and "Exit" buttons
    sf::RectangleShape sellButton(sf::Vector2f(200, 50));
    sellButton.setPosition(overlay.getPosition().x + 200, overlay.getPosition().y + 250);
    sellButton.setFillColor(sf::Color::Green);

    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setPosition(overlay.getPosition().x + 200, overlay.getPosition().y + 320);
    exitButton.setFillColor(sf::Color::Red);

    // Set up the texts for the buttons
    sf::Text sellText("Sell", font, 24);
    sellText.setFillColor(sf::Color::White);
    sellText.setPosition(sellButton.getPosition().x + (sellButton.getSize().x / 2) - sellText.getGlobalBounds().width / 2,
                         sellButton.getPosition().y + (sellButton.getSize().y / 2) - sellText.getGlobalBounds().height / 2);

    sf::Text exitText("Exit", font, 24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(exitButton.getPosition().x + (exitButton.getSize().x / 2) - exitText.getGlobalBounds().width / 2,
                         exitButton.getPosition().y + (exitButton.getSize().y / 2) - exitText.getGlobalBounds().height / 2);

    // Display the player's properties
    std::vector<std::shared_ptr<Location>> properties = player.getPropertiesOwned();
    std::vector<sf::Text> propertyTexts;
    for (size_t i = 0; i < properties.size(); ++i) {
        int price = properties[i]->getCost() + properties[i]->getHouseCost() * properties[i]->getHouseCount();
        if (properties[i]->hasHotel()) {
            price += properties[i]->getHotelCost();
        }
        sf::Text propertyText(properties[i]->getName() + " - Sell for $" + std::to_string(price), font, 20);
        propertyText.setFillColor(sf::Color::Black);
        propertyText.setPosition(overlay.getPosition().x + 50, overlay.getPosition().y + 50 + i * 30);
        propertyTexts.push_back(propertyText);
    }

    // Main loop for handling the Sell Menu events
    bool inSellMenu = true;
    while (inSellMenu && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check for mouse click events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                // Check if a property was clicked
                for (size_t i = 0; i < propertyTexts.size(); ++i) {
                    if (propertyTexts[i].getGlobalBounds().contains(mousePos)) {
                        // Sell the selected property
                        int price = properties[i]->getCost() + properties[i]->getHouseCost() * properties[i]->getHouseCount();
                        if (properties[i]->hasHotel()) {
                            price += properties[i]->getHotelCost();
                        }
                        player.updateCashInHand(price);
                        player.removeProperty(properties[i]);
                        player.setTempMessage("Sold " + properties[i]->getName() + " for $" + std::to_string(price));
                        properties[i]->reset();
                        inSellMenu = false;
                        break;
                    }
                }

                // Check if the "Exit" button was clicked
                if (exitButton.getGlobalBounds().contains(mousePos)) {
                    inSellMenu = false; // Close the menu
                }
            }
        }

        // Draw the sell menu overlay
        gameBoard.draw(window);
        gameBoard.drawPlayerMarkers(window, players); // Redraw all player markers
        window.draw(overlay);
        window.draw(sellButton);
        window.draw(exitButton);
        window.draw(sellText);
        window.draw(exitText);

        // Draw the property texts
        for (const auto &text : propertyTexts) {
            window.draw(text);
        }

        window.display();
    }
}




        void BuyMenu(Player* currentPlayer, std::shared_ptr<Location> currentLocation, sf::RenderWindow &window, sf::Font& font, Board& gameBoard,std::vector<Player>& players) {
    // Create the overlay rectangle for the Buy Menu
    sf::RectangleShape overlay(sf::Vector2f(600, 400));
    overlay.setFillColor(sf::Color(255, 255, 255, 200)); // Semi-transparent white background
    overlay.setPosition((window.getSize().x - 1000) / 2, (window.getSize().y - 400) / 2); // Center the overlay

    // Set up the "Buy" and "Exit" buttons
    sf::RectangleShape buyButton(sf::Vector2f(200, 50));
    buyButton.setPosition(overlay.getPosition().x + 200, overlay.getPosition().y + 250);
    buyButton.setFillColor(sf::Color::Green);

    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setPosition(overlay.getPosition().x + 200, overlay.getPosition().y + 320);
    exitButton.setFillColor(sf::Color::Red);

    // Set up the texts for the buttons
    sf::Text buyText("Buy", font, 24);
    buyText.setFillColor(sf::Color::White);
    buyText.setPosition(buyButton.getPosition().x + (buyButton.getSize().x / 2) - buyText.getGlobalBounds().width / 2,
                        buyButton.getPosition().y + (buyButton.getSize().y / 2) - buyText.getGlobalBounds().height / 2);

    sf::Text exitText("Exit", font, 24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(exitButton.getPosition().x + (exitButton.getSize().x / 2) - exitText.getGlobalBounds().width / 2,
                         exitButton.getPosition().y + (exitButton.getSize().y / 2) - exitText.getGlobalBounds().height / 2);

    // Display the property details and player's cash
    sf::Text propertyInfo("Would you like to buy " + currentLocation->getName() + " for $" + std::to_string(currentLocation->getCost()) + "?", font, 15);
    propertyInfo.setFillColor(sf::Color::Black);
    propertyInfo.setPosition(overlay.getPosition().x + 50, overlay.getPosition().y + 50);

    sf::Text cashInfo("You have: $" + std::to_string(currentPlayer->getCashInHand()), font, 20);
    cashInfo.setFillColor(sf::Color::Black);
    cashInfo.setPosition(overlay.getPosition().x + 50, overlay.getPosition().y + 120);

    // Text for displaying "Not enough money" message
    sf::Text notEnoughMoneyText("Not enough money to buy this property!", font, 20);
    notEnoughMoneyText.setFillColor(sf::Color::Red);
    notEnoughMoneyText.setPosition(overlay.getPosition().x + 150, overlay.getPosition().y + 200);
    bool showNotEnoughMoney = false;

    // Main loop for handling the Buy Menu events
    bool inBuyMenu = true;
    while (inBuyMenu && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check for mouse click events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                // Check if the "Buy" button was clicked
                if (buyButton.getGlobalBounds().contains(mousePos)) {
                    if (currentPlayer->getCashInHand() >= currentLocation->getCost()) {
                        currentPlayer->updateCashInHand(-currentLocation->getCost());
                        currentPlayer->updateNetWorth(currentLocation->getCost() * 2);
                        currentLocation->setOwner(currentPlayer);
                        currentPlayer->addProperty(currentLocation);
                        std::cout << currentPlayer->getName() << " bought " << currentLocation->getName() << std::endl;
                        currentPlayer->setTempMessage(currentPlayer->getName() + " bought " + currentLocation->getName());
                        inBuyMenu = false;  // Close the menu after purchase
                    } else {
                        // Display "Not enough money" message
                        showNotEnoughMoney = true;
                    }
                }

                // Check if the "Exit" button was clicked
                if (exitButton.getGlobalBounds().contains(mousePos)) {
                    std::cout << currentPlayer->getName() << " chose not to buy " << currentLocation->getName() << std::endl;
                    inBuyMenu = false;  // Close the menu
                }
            }
        }

        // Draw all elements of the main game

        gameBoard.draw(window);
        gameBoard.drawPlayerMarkers(window, players); // Redraw all player markers



        // Draw the overlay elements
        window.draw(overlay);
        window.draw(buyButton);
        window.draw(exitButton);
        window.draw(buyText);
        window.draw(exitText);
        window.draw(propertyInfo);
        window.draw(cashInfo);

        // Display the "Not enough money" message if applicable
        if (showNotEnoughMoney) {
            window.draw(notEnoughMoneyText);
        }

        // Display everything
        window.display();
    }

    // Update the player markers after exiting the buy menu
    gameBoard.drawPlayerMarkers(window, players);
    window.display();
}




void BankruptByPlayer(Player *CurrentPlayer,Player* owner) {

    vector<std::shared_ptr<Location>> property=CurrentPlayer->getPropertiesOwned();
        for(std::shared_ptr<Location> loc:property){
            loc->setOwner(owner); // update the new owner
            owner->addProperty(loc);
            owner->updateNetWorth(loc->getCost());
        }
        CurrentPlayer->clearProperties();
    CurrentPlayer->setBankrupct();


}

bool checkAndDisplayWinner(std::vector<Player>& players, sf::RenderWindow &window, sf::Font &font) {


    // Create a background for the results display
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(50, 50, 50, 200));

    // Check if a player has won by reaching $4000
    for (const auto& player : players) {
        if (player.getCashInHand() >= 4000) {
            // Clear the window and display the results
            // Sort players by their cash in hand in descending order
            std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
                return a.getCashInHand() > b.getCashInHand();
            });
            window.clear();
            window.draw(background);

            sf::Text winnerText("Congratulations " + player.getName() + "! You have reached $4000 and won the game!", font, 30);
            winnerText.setFillColor(sf::Color::White);
            winnerText.setPosition((window.getSize().x - winnerText.getGlobalBounds().width) / 2, 50);
            window.draw(winnerText);

            // Display the final standings
            for (size_t i = 0; i < players.size(); ++i) {
                sf::Text playerText(std::to_string(i + 1) + ". " + players[i].getName() + " - Cash: $" + std::to_string(players[i].getCashInHand()), font, 24);
                playerText.setFillColor(sf::Color::White);
                playerText.setPosition(100, 120 + i * 40); // Adjust position as needed
                window.draw(playerText);
            }

            window.display();
            sf::sleep(sf::seconds(5));  // Display the results for 5 seconds
            return true;
        }
    }

    // Check if only one player is not bankrupt
    int activePlayers = 0;
    Player* lastActivePlayer = nullptr;
    for (auto& player : players) {
        if (!player.isBankrupct()) {
            activePlayers++;
            lastActivePlayer = &player;
        }
    }

    if (activePlayers == 1 && lastActivePlayer != nullptr) {
        // Sort players by their cash in hand in descending order
        std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
            return a.getCashInHand() > b.getCashInHand();
        });
        // Clear the window and display the results
        window.clear();
        window.draw(background);

        sf::Text winnerText("Congratulations " + lastActivePlayer->getName() + "! You are the last player standing and have won the game!", font, 30);
        winnerText.setFillColor(sf::Color::White);
        winnerText.setPosition((window.getSize().x - winnerText.getGlobalBounds().width) / 2, 50);
        window.draw(winnerText);

        // Display the final standings
        for (size_t i = 0; i < players.size(); ++i) {
            sf::Text playerText(std::to_string(i + 1) + ". " + players[i].getName() + " - Cash: $" + std::to_string(players[i].getCashInHand()), font, 24);
            playerText.setFillColor(sf::Color::White);
            playerText.setPosition(100, 120 + i * 40); // Adjust position as needed
            window.draw(playerText);
        }

        window.display();
        sf::sleep(sf::seconds(5));  // Display the results for 5 seconds
        return true;
    }


    return false;
}
