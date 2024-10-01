//
// Created by elnatan on 06/09/2024.
//

#include "Dice.hpp"
// Constructor initializes random number generator
Dice::Dice() : rng(std::random_device{}()) {
    die1 = die2 = 0;
}

// Roll both dice and return the total
int Dice::roll() {
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 6); // Rolling between 1 and 6
    die1 = dist(rng);
    die2 = dist(rng);

    return die1 + die2;  // Return the sum of both dice
}

// Get individual dice values
int Dice::getDie1() const { return die1; }
int Dice::getDie2() const { return die2; }
int Dice::getRoll() const { return die1+die2; }
bool Dice::isDouble(){
    return  die1==die2;
}

// Print dice results
void Dice::printRoll() const {
    std::cout << "rolled: " << die1 << " and " << die2 << " (Total: " << (die1 + die2) << ")" << std::endl;
}