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

#define clearScreen() system("@cls||clear")
#define goto_XY(X, Y) printf("%c[%d;%df", 0x1B, Y, X)
#define hideCursor() printf("\e[?25l")
#define showCursor() printf("\e[?25h")
#define colour(C1, C2) printf("\033[%d;%dm", C2, C1)


enum colours
{
    RESET,
    INCREASED_INTENSITY,
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
    RED_BG = 41,
    GREEN_BG,
    YELLOW_BG,
    BLUE_BG,
    PURPLE_BG,
    CYAN_BG,
    WHITE_BG,
    LIGHTBLACK_BG = 100,
    LIGHTRED_BG,
    LIGHTGREEN_BG,
    LIGHTYELLOW_BG,
    LIGHTBLUE_BG,
    LIGHTPURPLE_BG,
    LIGHTCYAN_BG,
    PUREWHITE_BG
};
enum GameMode
{
    NETWORTH,
    TURNS,
    ENDLESS,
    EXIT
};

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
enum MainMenu
{
    ROLL,
    BUY,
    SELL,
    GIVEUP
};

// Structure containing location information
                      // Locations read from csv file

// Structure containing card information


#endif
