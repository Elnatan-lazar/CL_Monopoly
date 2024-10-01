#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

// System specific
#define SCREENSIZE_X 172
#define SCREENSIZE_Y 40

// Can be changed according to game requirement
#define INITIAL_AMT 1200    // Amount of money each player start with
#define BANKRUPT_VALUE -500 // Min value of cash in hand to be not bankrupt
#define MAX_DOUBLES 3       // Maximum die doubles a player can roll

// Path location of csv file
#define LOCATION_PATH "data/locations.csv"

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>



#ifdef _WIN32
#include <conio.h>
#endif



enum LocType
{
    FREE,
    CHEST,
    CHANCE,
    JAIL,
    TAX,
    UTILITY,
    RAIL,
    PROPERTY
};
enum CardType
{
    BAD = -1,
    NEUTRAL,
    GOOD
};




#endif
