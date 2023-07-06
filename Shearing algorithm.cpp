#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main()
{
    // Window size
    const int WIDTH = 800;
    const int HEIGHT = 600;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Shearing Example");

    // Create a rectangle shape
    sf::RectangleShape rectangle(sf::Vector2f(200.0f, 100.0f));
    rectangle.setPosition(WIDTH / 2.0f, HEIGHT / 2.0f);
    rectangle.setOrigin(100.0f, 50.0f);
    rectangle.setFillColor(sf::Color::Red);

    // Shearing factor
    float shearFactor = 0.0f;
    bool increasing = true;

    // Animation speed
    float animationSpeed = 0.01f;

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

        // Update the shearing factor
        if (increasing)
        {
            shearFactor += animationSpeed;
            if (shearFactor >= 0.5f)
                increasing = false;
        }
        else
        {
            shearFactor -= animationSpeed;
            if (shearFactor <= -0.5f)
                increasing = true;
        }

        // Create a sheared rectangle shape
        sf::ConvexShape shearedRect;
        shearedRect.setPointCount(4);
        shearedRect.setPoint(0, sf::Vector2f(rectangle.getPosition().x, rectangle.getPosition().y));
        shearedRect.setPoint(1, sf::Vector2f(rectangle.getPosition().x + rectangle.getSize().x, rectangle.getPosition().y));
        shearedRect.setPoint(2, sf::Vector2f(rectangle.getPosition().x + rectangle.getSize().x + rectangle.getSize().y * shearFactor, rectangle.getPosition().y + rectangle.getSize().y));
        shearedRect.setPoint(3, sf::Vector2f(rectangle.getPosition().x + rectangle.getSize().y * shearFactor, rectangle.getPosition().y + rectangle.getSize().y));
        shearedRect.setFillColor(rectangle.getFillColor());

        // Draw the original and sheared rectangle
   
        window.draw(shearedRect);

        // Update the window
        window.display();

        // Delay between frames
        sf::sleep(sf::milliseconds(16)); // 60 FPS (1000 ms / 60)
    }

    return 0;
}

