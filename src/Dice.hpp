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
    Dice() : rng(std::random_device{}()) {
        die1 = die2 = 0;
    }

    // Roll both dice and return the total
    int roll() {
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 6); // Rolling between 1 and 6
        die1 = dist(rng);
        die2 = dist(rng);

        return die1 + die2;  // Return the sum of both dice
    }

    // Get individual dice values
    int getDie1() const { return die1; }
    int getDie2() const { return die2; }
    int getRoll() const { return die1+die2; }
    bool isDouble(){
        return  die1==die2;
    }

    // Print dice results
    void printRoll() const {
        std::cout << "rolled: " << die1 << " and " << die2 << " (Total: " << (die1 + die2) << ")" << std::endl;
    }
};

#endif // DICE_HPP
