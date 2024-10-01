
#include "maingame.hpp"
#include <SFML/Graphics.hpp>
#include "action.hpp"



int main()
{

    // Get the desktop resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Create a window in full-screen mode
    sf::RenderWindow window(desktop, "Monopoly Game", sf::Style::Fullscreen);

    // Load a background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("openScreen.jpg"))  // Replace with your image path
    {
        return -1; // Exit if the background image couldn't be loaded
    }

    // Create a sprite to hold the background texture
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Resize the background sprite to fit the window size
    backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("ALBAS.ttf"))
    {
        return -1; // Exit if the font couldn't be loaded
    }

    // Create buttons
    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    sf::RectangleShape rulesButton(sf::Vector2f(200, 50));
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));

    sf::Text playText = createButtons(font, playButton, 850, 200, "Play", sf::Color::Green);
    sf::Text rulesText = createButtons(font, rulesButton, 850, 300, "Read Rules", sf::Color::Blue);
    sf::Text exitText = createButtons(font, exitButton, 850, 400, "Exit", sf::Color::Red);

    // Main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            // Check for window resize event
            if (event.type == sf::Event::Resized)
            {
                // Update the view according to the new window size
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                // Resize the background sprite to fit the new window size
                backgroundSprite.setScale(
                        static_cast<float>(event.size.width) / backgroundTexture.getSize().x,
                        static_cast<float>(event.size.height) / backgroundTexture.getSize().y
                );
            }

            // Check for mouse button press
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Translate mouse position to current window coordinates
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if (playButton.getGlobalBounds().contains(mousePos))
                    {
                        mainGame(window, font);
                        return  1;
                    }
                    else if (rulesButton.getGlobalBounds().contains(mousePos))
                    {
                        ShowRules(window, font);
                    }
                    else if (exitButton.getGlobalBounds().contains(mousePos))
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear();                         // Clear the window
        window.draw(backgroundSprite);          // Draw the background first
        window.draw(playButton);                // Draw the play button
        window.draw(rulesButton);               // Draw the rules button
        window.draw(exitButton);                // Draw the exit button
        window.draw(playText);                  // Draw the play button text
        window.draw(rulesText);                 // Draw the rules button text
        window.draw(exitText);                  // Draw the exit button text
        window.display();                       // Display everything
    }

    return EXIT_SUCCESS;
}