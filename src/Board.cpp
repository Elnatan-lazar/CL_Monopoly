#include "Board.hpp"
#include "Location.hpp"
#include "Player.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <unordered_map>

using namespace std;
// Constructor: Initialize all the 40 locations according to the standard Monopoly board layout
Board::Board() {
    // Add all 40 locations in ID order
    locations.push_back(std::make_shared<Location>(1, FREE, "START", sf::Color::White));  // Start
    locations.push_back(std::make_shared<Location>(2, PROPERTY, "MEDITERRANEAN AVENUE", sf::Color(165, 42, 42), 60, 2, 50, 250, 160));  // Brown
    locations.push_back(std::make_shared<Location>(3, CHEST, "COMMUNITY CHEST", sf::Color::White));  // Community Chest
    locations.push_back(std::make_shared<Location>(4, PROPERTY, "BALTIC AVENUE", sf::Color(165, 42, 42), 60, 4, 50, 320, 180));  // Brown
    locations.push_back(std::make_shared<Location>(5, TAX, "INCOME TAX", sf::Color::White, 200));  // Income Tax
    locations.push_back(std::make_shared<Location>(6, RAIL, "READING RAILROAD", sf::Color::Black, 200, 25));  // Railroad
    locations.push_back(std::make_shared<Location>(7, PROPERTY, "ORIENTAL AVENUE", sf::Color(173, 216, 230), 100, 6, 50, 400, 270));  // Light Blue
    locations.push_back(std::make_shared<Location>(8, CHANCE, "CHANCE", sf::Color::White));  // Chance
    locations.push_back(std::make_shared<Location>(9, PROPERTY, "VERMONT AVENUE", sf::Color(173, 216, 230), 100, 6, 50, 400, 270));  // Light Blue
    locations.push_back(std::make_shared<Location>(10, PROPERTY, "CONNECTICUT AVENUE", sf::Color(173, 216, 230), 120, 8, 50, 450, 300));  // Light Blue
    locations.push_back(std::make_shared<Location>(11, FREE, "JUST VISITING / IN JAIL", sf::Color::White));  // Jail
    locations.push_back(std::make_shared<Location>(12, PROPERTY, "ST. CHARLES PLACE", sf::Color(255, 105, 180), 140, 10, 100, 625, 450));  // Pink
    locations.push_back(std::make_shared<Location>(13, UTILITY, "ELECTRIC COMPANY", sf::Color::White, 150, 0));  // Utility
    locations.push_back(std::make_shared<Location>(14, PROPERTY, "STATES AVENUE", sf::Color(255, 105, 180), 140, 10, 100, 625, 450));  // Pink
    locations.push_back(std::make_shared<Location>(15, PROPERTY, "VIRGINIA AVENUE", sf::Color(255, 105, 180), 160, 12, 100, 700, 500));  // Pink
    locations.push_back(std::make_shared<Location>(16, RAIL, "PENNSYLVANIA RAILROAD", sf::Color::Black, 200, 25));  // Railroad
    locations.push_back(std::make_shared<Location>(17, PROPERTY, "ST. JAMES PLACE", sf::Color(255, 165, 0), 180, 14, 100, 750, 550));  // Orange
    locations.push_back(std::make_shared<Location>(18, CHEST, "COMMUNITY CHEST", sf::Color::White));  // Community Chest
    locations.push_back(std::make_shared<Location>(19, PROPERTY, "TENNESSEE AVENUE", sf::Color(255, 165, 0), 180, 14, 100, 750, 550));  // Orange
    locations.push_back(std::make_shared<Location>(20, PROPERTY, "NEW YORK AVENUE", sf::Color(255, 165, 0), 200, 16, 100, 800, 600));  // Orange
    locations.push_back(std::make_shared<Location>(21, FREE, "FREE PARKING", sf::Color::White));  // Free Parking
    locations.push_back(std::make_shared<Location>(22, PROPERTY, "KENTUCKY AVENUE", sf::Color(255, 0, 0), 220, 18, 150, 1050, 700));  // Red
    locations.push_back(std::make_shared<Location>(23, CHANCE, "CHANCE", sf::Color::White));  // Chance
    locations.push_back(std::make_shared<Location>(24, PROPERTY, "INDIANA AVENUE", sf::Color(255, 0, 0), 220, 18, 150, 1050, 700));  // Red
    locations.push_back(std::make_shared<Location>(25, PROPERTY, "ILLINOIS AVENUE", sf::Color(255, 0, 0), 240, 20, 150, 1100, 750));  // Red
    locations.push_back(std::make_shared<Location>(26, RAIL, "B. & O. RAILROAD", sf::Color::Black, 200, 25));  // Railroad
    locations.push_back(std::make_shared<Location>(27, PROPERTY, "ATLANTIC AVENUE", sf::Color(255, 255, 0), 260, 22, 150, 1150, 800));  // Yellow
    locations.push_back(std::make_shared<Location>(28, PROPERTY, "VENTNOR AVENUE", sf::Color(255, 255, 0), 260, 22, 150, 1150, 800));  // Yellow
    locations.push_back(std::make_shared<Location>(29, UTILITY, "WATER WORKS", sf::Color::White, 150, 0));  // Utility
    locations.push_back(std::make_shared<Location>(30, PROPERTY, "MARVIN GARDENS", sf::Color(255, 255, 0), 280, 24, 150, 1200, 850));  // Yellow
    locations.push_back(std::make_shared<Location>(31, JAIL, "GO TO JAIL", sf::Color::White));  // Go to Jail
    locations.push_back(std::make_shared<Location>(32, PROPERTY, "PACIFIC AVENUE", sf::Color(0, 128, 0), 300, 26, 200, 1275, 900));  // Green
    locations.push_back(std::make_shared<Location>(33, PROPERTY, "NORTH CAROLINA AVENUE", sf::Color(0, 128, 0), 300, 26, 200, 1275, 900));  // Green
    locations.push_back(std::make_shared<Location>(34, CHEST, "COMMUNITY CHEST", sf::Color::White));  // Community Chest
    locations.push_back(std::make_shared<Location>(35, PROPERTY, "PENNSYLVANIA AVENUE", sf::Color(0, 128, 0), 320, 28, 200, 1400, 1000));  // Green
    locations.push_back(std::make_shared<Location>(36, RAIL, "SHORT LINE", sf::Color::Black, 200, 25));  // Railroad
    locations.push_back(std::make_shared<Location>(37, CHANCE, "CHANCE", sf::Color::White));  // Chance
    locations.push_back(std::make_shared<Location>(38, PROPERTY, "PARK PLACE", sf::Color(0, 0, 128), 350, 35, 200, 1500, 1100));  // Dark Blue
    locations.push_back(std::make_shared<Location>(39, TAX, "LUXURY TAX", sf::Color::White, 100));  // Luxury Tax
    locations.push_back(std::make_shared<Location>(40, PROPERTY, "BOARDWALK", sf::Color(0, 0, 128), 400, 50, 200, 2000, 1400));  // Dark Blue

    // Establishing same-color sets
    for (auto &location : locations) {
        if (location->getType() == PROPERTY || location->getType() == RAIL) {
            for (auto &otherLocation : locations) {
                if (otherLocation != location && otherLocation->getType() == location->getType() && otherLocation->getColor() == location->getColor()) {
                    location->addSameColorLocation(otherLocation);
                }
            }
        }
    }

    sf::Font font;
    if (!font.loadFromFile("ALBAS.ttf"))
    {
        std::cout <<" font not found";
    }

}

Board::~Board() {
    // Destructor automatically handles shared_ptr cleanup
}

void Board::draw(sf::RenderWindow &window) {
    const float boardSize = 1100.0f;  // Set board size to 1100x1100
    const int totalSquares = 40;  // Total squares on the Monopoly board
    const int squaresPerSide = 11; // Number of squares per side of the board
    const float squareSize = boardSize / squaresPerSide; // Size of each square
    const sf::Vector2f boardOffset(100, (window.getSize().y - boardSize) / 2); // Position on the left side, shifted right by 100 pixels

    // Load the font, make sure the path is correct
    sf::Font font;
    if (!font.loadFromFile("ALBAS.ttf")) {  // Ensure the font path is correct
        std::cerr << "Error loading font\n";
        return;
    }

    // Draw all 40 locations in their respective positions
    for (size_t i = 0; i < totalSquares; ++i) {
        int row, col;
        if (i < 10) {  // Bottom row
            row = squaresPerSide - 1;
            col = squaresPerSide - 1 - i;
        } else if (i < 20) {  // Left column
            row = squaresPerSide - 1 - (i - 10);
            col = 0;
        } else if (i < 30) {  // Top row
            row = 0;
            col = i - 20;
        } else {  // Right column
            row = i - 30;
            col = squaresPerSide - 1;
        }

        // Set up square shape for the location
        sf::RectangleShape squareShape(sf::Vector2f(squareSize, squareSize));
        squareShape.setPosition(boardOffset.x + col * squareSize, boardOffset.y + row * squareSize);
        squareShape.setFillColor(locations[i]->getColor());
        squareShape.setOutlineThickness(2);
        squareShape.setOutlineColor(sf::Color(169, 169, 169)); // Add border

        // Draw the square on the window
        window.draw(squareShape);

        // Display the location name and price as a string
        std::string displayText = locations[i]->getName();
        if (locations[i]->getType() == PROPERTY || locations[i]->getType() == UTILITY || locations[i]->getType() == RAIL) {
            displayText += "\n$" + std::to_string(locations[i]->getCost());
        }

        // Create an sf::Text to display this information
        sf::Text locationText(displayText, font, 10);  // Use a smaller initial size
        locationText.setFillColor(sf::Color(169, 169, 169));

        // Adjust the text size to fit within the square
        while (locationText.getLocalBounds().width > squareSize - 10 || locationText.getLocalBounds().height > squareSize - 10) {
            locationText.setCharacterSize(locationText.getCharacterSize() - 1);
        }

        // Center the text inside the square
        sf::FloatRect textRect = locationText.getLocalBounds();
        locationText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        locationText.setPosition(squareShape.getPosition().x + squareSize / 2, squareShape.getPosition().y + squareSize / 2);

        // Draw the text
        window.draw(locationText);

        // Draw houses (*) and hotels (#) based on ownership
        if (locations[i]->hasHotel() || locations[i]->getHouseCount() > 0) {
            std::string houseHotelDisplay;
            sf::Color ownerColor = locations[i]->getOwner() ? locations[i]->getOwner()->getColor() : sf::Color::White;

            if (locations[i]->hasHotel()) {
                houseHotelDisplay = "#";  // Display hotel as '#'
            } else {   // Display houses as '*'
                switch (locations[i]->getHouseCount()) {
                    case 1:
                        houseHotelDisplay = std::string(locations[i]->getHouseCount(), '*');
                        break;
                    case 2:
                        houseHotelDisplay = std::string(locations[i]->getHouseCount(), '**');
                        break;
                    case 3:
                        houseHotelDisplay = std::string(locations[i]->getHouseCount(), '***');
                        break;
                    default:
                        houseHotelDisplay = std::string(locations[i]->getHouseCount(), '****');
                        break;
                }

            }

            // Set up sf::Text to display the house/hotel marks
            sf::Text houseHotelText(houseHotelDisplay, font, 20);  // Adjust size for visibility
            houseHotelText.setFillColor(ownerColor);

            // Position the house/hotel text at the bottom center of the square
            sf::FloatRect textRect = houseHotelText.getLocalBounds();
            houseHotelText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            houseHotelText.setPosition(squareShape.getPosition().x + squareSize / 2,
                                       squareShape.getPosition().y + squareSize - 15);

            // Draw the house/hotel text
            window.draw(houseHotelText);
        }
    }
}

int Board::getNumSquares() const {
    return static_cast<int>(std::ceil(std::sqrt(locations.size())));
}

void Board::drawPlayerMarkers(sf::RenderWindow &window, const std::vector<Player> &players) {
    const float boardSize = 1100.0f;  // Match the new board size used in your draw function
    const int totalSquares = 40;  // Total squares on the Monopoly board
    const int squaresPerSide = 11; // Number of squares per side of the board
    const float squareSize = boardSize / squaresPerSide; // Size of each square
    const sf::Vector2f boardOffset(100, (window.getSize().y - boardSize) / 2); // Position the boardOffset correctly

    // Map to keep track of players at each position
    std::unordered_map<int, std::vector<const Player*>> positionMap;
    for (const auto &player : players) {
        if (!player.isBankrupct()) {
            int position = player.getCurrentLocation()->getID() - 1;
            positionMap[position].push_back(&player);
        }
    }

    // Draw player markers on the board
    for (const auto &entry : positionMap) {
        int position = entry.first;
        const std::vector<const Player*>& playersAtPosition = entry.second;
        int numPlayers = playersAtPosition.size();

        // Calculate grid layout parameters
        int maxMarkersPerRow = 3;  // Show at least 3 markers per row
        int rows = (numPlayers + maxMarkersPerRow - 1) / maxMarkersPerRow;  // Calculate number of rows needed
        float markerRadius = std::min(10.0f, (squareSize / (rows * 2.0f))); // Adjust marker radius based on rows

        // Determine the square's row and column
        int row, col;
        if (position < 10) {
            row = squaresPerSide - 1;
            col = squaresPerSide - 1 - position;
        } else if (position < 20) {
            row = squaresPerSide - 1 - (position - 10);
            col = 0;
        } else if (position < 30) {
            row = 0;
            col = position - 20;
        } else {
            row = position - 30;
            col = squaresPerSide - 1;
        }

        // Base position for the markers in the square
        float baseX = boardOffset.x + col * squareSize + (squareSize / 2) - (maxMarkersPerRow * markerRadius);
        float baseY = boardOffset.y + row * squareSize + (squareSize / 2) - (rows * markerRadius);

        // Draw each player marker
        for (int i = 0; i < numPlayers; ++i) {
            sf::CircleShape marker(markerRadius);
            marker.setFillColor(playersAtPosition[i]->getColor());
            marker.setOutlineColor(sf::Color::Black);
            marker.setOutlineThickness(1);

            int currentRow = i / maxMarkersPerRow;
            int currentCol = i % maxMarkersPerRow;

            // Adjust marker position within the square in a grid layout
            float offsetX = (currentCol * markerRadius * 2.5f);
            float offsetY = (currentRow * markerRadius * 2.5f);

            marker.setPosition(baseX + offsetX, baseY + offsetY);
            window.draw(marker);
        }
    }
}



std::vector<std::shared_ptr<Location>> Board::getLocations() {
    return locations;  // Return a reference to the vector of locations
}