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
    gameBoard.getLocations()[1]->buyHouse();
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
    // Set up the Buy House/Hotel menu window
    sf::RenderWindow menuWindow(sf::VideoMode(600, 600), "Buy House/Hotel");

    // Menu items
    sf::Text titleText = createText(font, "Buy House/Hotel Menu", 24, sf::Color::White, 20, 20);
    sf::Text instructionText = createText(font, "Select a property index to build:", 18, sf::Color::White, 20, 60);

    std::vector<std::shared_ptr<Location>> properties = currentPlayer.getPropertiesOwned();
    std::vector<std::shared_ptr<Location>> eligibleProperties;

    // Gather only the eligible properties with complete sets of the same color and of street type
    for (auto &property : properties) {
        if (property->getType() == PROPERTY && currentPlayer.ownsCompleteSet(property->getColor())) {
            eligibleProperties.push_back(property);
        }
    }

    std::vector<sf::Text> propertyTexts;
    for (size_t i = 0; i < eligibleProperties.size(); ++i) {
        sf::Text propText = createText(font, std::to_string(i + 1) + " - " + eligibleProperties[i]->getName(), 18, sf::Color::White, 20, 100 + static_cast<float>(i) * 30);
        propertyTexts.push_back(propText);
    }

    sf::Text exitButtonText = createText(font, "Exit", 20, sf::Color::White, 500, 550);
    sf::RectangleShape exitButton(sf::Vector2f(80, 40));
    exitButton.setPosition(500, 550);
    exitButton.setFillColor(sf::Color::Red);

    // Input for property index selection
    sf::Text inputPrompt = createText(font, "Enter property index:", 18, sf::Color::White, 20, 450);
    sf::Text inputFeedback = createText(font, "", 18, sf::Color::White, 20, 480);
    std::string input;
    bool validInput = false;
    int selectedPropertyIndex = -1;

    // Button for choosing house/hotel
    sf::Text chooseHouseText = createText(font, "Choose House", 20, sf::Color::White, 200, 520);
    sf::RectangleShape chooseHouseButton(sf::Vector2f(120, 40));
    chooseHouseButton.setPosition(200, 520);
    chooseHouseButton.setFillColor(sf::Color::Blue);

    sf::Text chooseHotelText = createText(font, "Choose Hotel", 20, sf::Color::White, 350, 520);
    sf::RectangleShape chooseHotelButton(sf::Vector2f(120, 40));
    chooseHotelButton.setPosition(350, 520);
    chooseHotelButton.setFillColor(sf::Color::Blue);

    bool isChoosingProperty = true;

    // Menu loop
    while (menuWindow.isOpen()) {
        sf::Event event;
        while (menuWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                menuWindow.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = menuWindow.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                // Check if the exit button is clicked
                if (exitButton.getGlobalBounds().contains(mousePos)) {
                    std::cout << "Exiting buy menu." << std::endl;
                    menuWindow.close();
                    return;
                }

                // Check if the Choose House button is clicked
                if (chooseHouseButton.getGlobalBounds().contains(mousePos) && validInput) {
                    std::cout << "Player chose to buy a house for property: " << eligibleProperties[selectedPropertyIndex]->getName() << std::endl;
                    if (eligibleProperties[selectedPropertyIndex]->buyHouse()) {
                        currentPlayer.updateCashInHand(-eligibleProperties[selectedPropertyIndex]->getHouseCost());
                        std::cout << "House purchased for " << eligibleProperties[selectedPropertyIndex]->getName() << std::endl;
                        menuWindow.close();
                        return;
                    } else {
                        inputFeedback.setString("Cannot buy house. Maximum houses reached.");
                    }
                }

                // Check if the Choose Hotel button is clicked
                if (chooseHotelButton.getGlobalBounds().contains(mousePos) && validInput) {
                    std::cout << "Player chose to buy a hotel for property: " << eligibleProperties[selectedPropertyIndex]->getName() << std::endl;
                    if (eligibleProperties[selectedPropertyIndex]->buyHotel()) {
                        currentPlayer.updateCashInHand(-eligibleProperties[selectedPropertyIndex]->getHotelCost());
                        std::cout << "Hotel purchased for " << eligibleProperties[selectedPropertyIndex]->getName() << std::endl;
                        menuWindow.close();
                        return;
                    } else {
                        inputFeedback.setString("Cannot buy hotel. Maximum houses needed first.");
                    }
                }
            }

            // Handling text input for property selection
            if (event.type == sf::Event::TextEntered && isChoosingProperty) {
                if (std::isdigit(event.text.unicode)) {
                    input += static_cast<char>(event.text.unicode);
                    inputFeedback.setString("Input: " + input);
                }

                // Check for backspace
                if (event.text.unicode == 8 && !input.empty()) {
                    input.pop_back();
                    inputFeedback.setString("Input: " + input);
                }

                // Check for enter key
                if (event.text.unicode == 13 && !input.empty()) {
                    int index = std::stoi(input) - 1;
                    if (index >= 0 && index < eligibleProperties.size()) {
                        selectedPropertyIndex = index;
                        validInput = true;
                        isChoosingProperty = false;
                        inputFeedback.setString("Selected: " + eligibleProperties[index]->getName());
                        std::cout << "Player selected property: " << eligibleProperties[index]->getName() << std::endl;
                    } else {
                        inputFeedback.setString("Invalid input. Enter valid index.");
                        input.clear();
                    }
                }
            }
        }

        // Clear the window
        menuWindow.clear(sf::Color(30, 30, 30));

        // Draw all elements
        menuWindow.draw(titleText);
        menuWindow.draw(instructionText);
        for (auto &propText : propertyTexts) {
            menuWindow.draw(propText);
        }

        menuWindow.draw(exitButton);
        menuWindow.draw(exitButtonText);

        if (validInput) {
            menuWindow.draw(chooseHouseButton);
            menuWindow.draw(chooseHouseText);
            menuWindow.draw(chooseHotelButton);
            menuWindow.draw(chooseHotelText);
        }

        menuWindow.draw(inputPrompt);
        menuWindow.draw(inputFeedback);

        // Display everything
        menuWindow.display();
    }
}







