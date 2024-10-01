#ifndef DICE_HPP
#define DICE_HPP

#include <random>
#include <ctime>
#include <iostream>

class Dice {
private:
    int die1, die2;  // Values of the two dice
    std::mt19937 rng;  // Random number generator

public:
    // Constructor initializes random number generator
    Dice() ;

    // Roll both dice and return the total
    int roll();

    // Get individual dice values
    int getDie1() const ;
    int getDie2() const ;
    int getRoll() const ;
    bool isDouble();

    // Print dice results
    void printRoll() const ;
};

#endif // DICE_HPP
