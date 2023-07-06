#include <SFML/Graphics.hpp>

int main()
{
    // Window size
    const int WIDTH = 800;
    const int HEIGHT = 600;

    // Translation values
    float translateX = 100.0f;
    float translateY = 100.0f;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Translation Example");

    // Game loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw a rectangle before translation
        sf::RectangleShape rectangle(sf::Vector2f(100.0f, 100.0f));
        rectangle.setPosition(100.0f, 100.0f);
        rectangle.setFillColor(sf::Color::Red);
        window.draw(rectangle);

        // Perform translation
        sf::RectangleShape translatedRect(sf::Vector2f(100.0f, 100.0f));
        translatedRect.setPosition(100.0f + translateX, 100.0f + translateY);
        translatedRect.setFillColor(sf::Color::Green);
        window.draw(translatedRect);

        // Update the window
        window.display();
    }

    return 0;
}

