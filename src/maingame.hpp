#ifndef MAINGAME_H_
#define MAINGAME_H_

#include "definitions.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Location.hpp"
#include "Dice.hpp"
#include <SFML/Graphics.hpp>
#include <string>



sf::Text createButtons(sf::Font &font,sf::RectangleShape &playButton,int posX,int posY,std::string massage,sf::Color color);




// Clears screen and displays rules of monopoly
// Returns EXIT_SUCCESS when displayed properly
void ShowRules( sf::RenderWindow &window, sf::Font &font);

// Clears screen and displays rules of monopoly
// Returns EXIT_SUCCESS after game played successfully
void mainGame(sf::RenderWindow &window, sf::Font &font);

void buyHouse(Player& currentPlayer,sf::RenderWindow& window, sf::Font& font);

void showPropertiesWindow(Player &player, sf::Font &font);




sf::Text createText(const sf::Font &font, const std::string &str, unsigned int size, sf::Color color, float x, float y);

#endif
