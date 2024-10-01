#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>  // Include for shared_ptr
#include "Location.hpp"


class Board {
private:
    std::vector<std::shared_ptr<Location>> locations;  // Using shared_ptr for memory management
    sf::RectangleShape squareShape;    // Shape for each square on the board
    sf::Font font;                     // Font for displaying text on the board

public:
    Board();
    ~Board();
    void draw(sf::RenderWindow &window); // Function to draw the board
    void drawPlayerMarkers(sf::RenderWindow &window, const std::vector<Player> &players);
    std::vector<std::shared_ptr<Location>> getLocations(); // Return reference to the vector of locations
    int getNumSquares() const; // Function to get the number of squares per row/column
};

#endif // BOARD_HPP



