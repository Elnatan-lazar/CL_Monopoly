// action.cpp
#include "action.hpp"

// Function to create a text element
sf::Text createText(const sf::Font &font, const std::string &str, unsigned int size, sf::Color color, float x, float y) {
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    return text;
}

// Function to create a button with text
sf::RectangleShape createButton(sf::RectangleShape &button, sf::Text &text, const sf::Font &font, const std::string &label, float x, float y, sf::Color buttonColor, sf::Color textColor) {
    button.setSize(sf::Vector2f(200, 50)); // Default button size
    button.setPosition(x, y);
    button.setFillColor(buttonColor);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24); // You can adjust this size
    text.setFillColor(textColor);
    // Center the text within the button
    text.setPosition(
            x + (button.getSize().x - text.getLocalBounds().width) / 2,
            y + (button.getSize().y - text.getLocalBounds().height) / 4
    );

    return button;
}

sf::Text createButtons(sf::Font &font,sf::RectangleShape &playButton,int posX,int posY,std::string massage,sf::Color color){
    playButton.setFillColor(color);
    playButton.setPosition(posX, posY);
    sf::Text playText(massage, font, 20);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(playButton.getPosition().x + 20, playButton.getPosition().y + 10);
    return playText;
}

void handleLandingAction(Player& player, Board& gameBoard, sf::RenderWindow& window, sf::Font& font, Dice& dice,std::vector<Player>& players) {
    switch (player.getCurrentLocation()->getType()) {
        case JAIL:
            player.setInJail(true);
            player.setJailTurn(3);
            player.setCurrentLocation(gameBoard.getLocations()[10]); // Set the player directly to the jail location
            player.setTempMessage("You are sent to Jail!");
            break;

        case TAX:
            player.updateCashInHand(-player.getCurrentLocation()->getRent());
            player.setTempMessage("You paid the tax of: "+std::to_string(player.getCurrentLocation()->getRent()));
            if (player.getCashInHand() < 0) {
                player.setBankrupct();
                player.resetProperties();
                player.setTempMessage("You are bankrupt!");
            }
            break;

        case PROPERTY:
        case UTILITY:
        case RAIL:
            if (!player.getCurrentLocation()->getOwner()) {
                BuyMenu(&player, player.getCurrentLocation(), window, font, gameBoard,players);
            } else if (player.getCurrentLocation()->getOwner()->getID() != player.getID()) {
                int rent = RentCalc(player.getCurrentLocation()->getOwner(), player.getCurrentLocation(), gameBoard, dice.getRoll());
                player.updateCashInHand(-rent);
                player.getCurrentLocation()->getOwner()->updateCashInHand(rent);
                if (player.getCashInHand() < 0) {
                    player.setBankrupct();
                    BankruptByPlayer(&player, player.getCurrentLocation()->getOwner());
                }
            }
            break;

        case CHANCE: {
            player.setTempMessage("You landed on Chance!");
            Card chanceCard = Card::drawChanceCard();  // Draw a random Chance card
            player.setTempMessage(chanceCard.getDescription());

            // Perform actions based on the card type
            switch (chanceCard.getType()) {
                case GOOD:
                    player.updateCashInHand(chanceCard.getMoney());
                    if(chanceCard.getDescription()=="Get out of Jail Free – This card may be kept until needed or traded"){
                        player.addOutOfJailCard();
                    }
                    break;
                case BAD:
                    if(chanceCard.getDescription()=="You are assessed for street repairs – $40 per house, $115 per hote;"){
                        int pay=0;
                        for(auto &property:player.getPropertiesOwned()){
                            if(property->getHouseCount()>0){
                                pay+=40*property->getHouseCount();
                            }
                            if(property->hasHotel()){
                                pay+=115;
                            }
                        }
                        player.updateCashInHand(-pay);
                        if (player.getCashInHand() < 0) {
                            player.setBankrupct();
                            player.resetProperties();
                            player.setTempMessage("You are bankrupt!");
                        }
                        break;
                    }
                    else if(chanceCard.getDescription()=="Make general repairs on all your property – For each house pay $25 – For each hotel $100")
                    {
                        int pay=0;
                        for(auto &property:player.getPropertiesOwned()){
                            if(property->getHouseCount()>0){
                                pay+=25*property->getHouseCount();
                            }
                            if(property->hasHotel()){
                                pay+=100;
                            }
                        }
                        player.updateCashInHand(-pay);
                        if (player.getCashInHand() < 0) {
                            player.setBankrupct();
                            player.resetProperties();
                            player.setTempMessage("You are bankrupt!");
                        }
                        break;
                    }
                    else if(chanceCard.getDescription()=="You have been elected Chairman of the Board – Pay each player $50") {
                        if (player.getCashInHand() < 50 * (players.size() - 1)) {
                            player.setBankrupct();
                            player.resetProperties();
                            player.setTempMessage("\n you are bankrupt!");
                        } else {
                            for (auto &p: players) {
                                if (p.getID() != player.getID()) {
                                    p.updateCashInHand(50);
                                    player.updateCashInHand(-50);
                                }
                            }
                        }
                        break;
                    }

                        player.updateCashInHand(-chanceCard.getMoney());
                        if (player.getCashInHand() < 0) {
                            player.setBankrupct();
                            player.resetProperties();
                            player.setTempMessage("You are bankrupt!");
                        }

                    break;
                case NEUTRAL:
                    if(chanceCard.getDescription()=="Take a trip to Reading Railroad – If you pass Go collect $200"){
                        if(player.getCurrentLocation()->getID()>6){
                            player.updateCashInHand(200);
                        }
                        player.setCurrentLocation(gameBoard.getLocations()[5]);
                        if(gameBoard.getLocations()[5]->getOwner()->getID()!=player.getID()){
                            player.updateCashInHand(-RentCalc(gameBoard.getLocations()[5]->getOwner(),gameBoard.getLocations()[5],gameBoard,dice.getRoll()));
                            if (player.getCashInHand() < 0) {
                                player.setBankrupct();
                                BankruptByPlayer(&player, gameBoard.getLocations()[5]->getOwner());
                            }
                        }
                        else{
                            BuyMenu(&player, gameBoard.getLocations()[5], window, font, gameBoard,players);
                        }
                        break;
                    }
                    if(chanceCard.getDescription()=="Advance to nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental to which they are otherwise entitled.")
                    {
                        int max=100;
                        int nearestRail=0;
                        for(auto &location:gameBoard.getLocations()){
                            if(location->getType()==RAIL){
                                if(abs(player.getCurrentLocation()->getID()-location->getID())<max){
                                    max=abs(player.getCurrentLocation()->getID()-location->getID());
                                    nearestRail=location->getID();
                                }
                            }
                        }
                        if(player.getCurrentLocation()->getID()>nearestRail){
                            player.updateCashInHand(200);
                        }
                        player.setCurrentLocation(gameBoard.getLocations()[nearestRail-1]);
                        if(gameBoard.getLocations()[nearestRail]->getOwner()->getID()!=player.getID()){
                            player.updateCashInHand(-2*RentCalc(gameBoard.getLocations()[nearestRail]->getOwner(),gameBoard.getLocations()[nearestRail],gameBoard,dice.getRoll()));
                            if (player.getCashInHand() < 0) {
                                player.setBankrupct();
                                BankruptByPlayer(&player, gameBoard.getLocations()[nearestRail]->getOwner());
                            }
                        }
                        else{
                            BuyMenu(&player, gameBoard.getLocations()[nearestRail], window, font, gameBoard,players);
                        }
                        break;
                    }
                    if(chanceCard.getDescription()=="Advance to nearest UTILITY. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental to which they are otherwise entitled.")
                    {
                        int max=100;
                        int nearestUTILITY=0;
                        for(auto &location:gameBoard.getLocations()){
                            if(location->getType()==UTILITY){
                                if(abs(player.getCurrentLocation()->getID()-location->getID())<max){
                                    max=abs(player.getCurrentLocation()->getID()-location->getID());
                                    nearestUTILITY=location->getID();
                                }
                            }
                        }
                        if(player.getCurrentLocation()->getID()>nearestUTILITY){
                            player.updateCashInHand(200);
                        }
                        player.setCurrentLocation(gameBoard.getLocations()[nearestUTILITY-1]);
                        if(gameBoard.getLocations()[nearestUTILITY-1]->getOwner()->getID()!=player.getID()){
                            player.updateCashInHand(-2*RentCalc(gameBoard.getLocations()[nearestUTILITY]->getOwner(),gameBoard.getLocations()[nearestUTILITY-1],gameBoard,dice.getRoll()));
                            if (player.getCashInHand() < 0) {
                                player.setBankrupct();
                                BankruptByPlayer(&player, gameBoard.getLocations()[nearestUTILITY]->getOwner());
                            }
                        }
                        else{
                            BuyMenu(&player, gameBoard.getLocations()[nearestUTILITY], window, font, gameBoard,players);
                        }
                        break;
                    }

                    if(player.getCurrentLocation()->getID()>chanceCard.getLocationID()){
                        player.updateCashInHand(200);
                    }
                    player.setCurrentLocation(gameBoard.getLocations()[chanceCard.getLocationID()]);


                    break;
            }

            // Handling the "Get out of Jail Free" card separately
            if (chanceCard.getDescription() == "Get out of Jail Free – This card may be kept until needed or traded") {
                player.addOutOfJailCard();
            }
            break;
        }

        case CHEST: {
            player.setTempMessage("You landed on Community Chest!");
            Card chestCard = Card::drawCommunityCard();  // Draw a random Community Chest card
            player.setTempMessage(chestCard.getDescription());

            // Perform actions based on the card type
            switch (chestCard.getType()) {
                case GOOD:
                    player.updateCashInHand(chestCard.getMoney());
                    break;
                case BAD:
                    player.updateCashInHand(-chestCard.getMoney());
                    if (player.getCashInHand() < 0) {
                        player.setBankrupct();
                        player.resetProperties();
                        player.setTempMessage("You are bankrupt!");
                    }
                    break;
                case NEUTRAL:
                    if (chestCard.getLocationID() != 0) {
                        player.setCurrentLocation(gameBoard.getLocations()[chestCard.getLocationID()]);
                    }
                    break;
            }
            break;
        }
    }
}
