#ifndef PLAYERMANU_HPP_
#define PLAYERMANU_HPP_
#include "definitions.hpp"
#include "playerManu.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Location.hpp"
#include "Dice.hpp"
#include <SFML/Graphics.hpp>
#include "action.hpp"


int ReadPlayers(sf::RenderWindow& window, sf::Font& font, std::vector<Player>& players);

void showJailMenu(Player& currentPlayer, sf::RenderWindow& window, sf::Font& font);



int SetPlayerOrder(sf::RenderWindow& window, sf::Font& font, std::vector<Player>& players);







// Calculates rent of location the player is currently on based on location type
// Returns rent of the location
int RentCalc(Player* owner, std::shared_ptr<Location> currentLocation, Board& board, int roll);

// Sell Menu for current player based on locations they own
// Returns EXIT_SUCCESS on success
void sellMenu(Player &player, sf::RenderWindow &window, sf::Font &font, Board& gameBoard, std::vector<Player>& players);



// Buy Property Menu for location player lands on
// Returns EXIT_SUCCESS on success
void BuyMenu(Player* currentPlayer, std::shared_ptr<Location> currentLocation, sf::RenderWindow &window, sf::Font& font, Board& gameBoard,std::vector<Player>& players);



// Shows leaderboards post game
// Returns EXIT_SUCCESS on successful display
int PlayerResults(std::vector<Player>& players);


void BankruptByPlayer(Player *CurrentPlayer, Player* owner);

#endif
