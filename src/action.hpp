// action.hpp
#ifndef ACTION_HPP
#define ACTION_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "definitions.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Card.hpp"
#include "Dice.hpp"
#include "playerManu.hpp"


// Function to create a text element
sf::Text createText(const sf::Font &font, const std::string &str, unsigned int size, sf::Color color, float x, float y);
void handleLandingAction(Player& player, Board& gameBoard, sf::RenderWindow& window, sf::Font& font, Dice& dice,std::vector<Player>& players);
// Function to create a button with text
sf::RectangleShape createButton(sf::RectangleShape &button, sf::Text &text, const sf::Font &font, const std::string &label, float x, float y, sf::Color buttonColor, sf::Color textColor);
sf::Text createButtons(sf::Font &font,sf::RectangleShape &playButton,int posX,int posY,std::string massage,sf::Color color);
#endif // ACTION_HPP
