#include <SFML/Graphics.hpp>

int main()
{
    // Window size
    const int WIDTH = 800;
    const int HEIGHT = 600;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Reflection Example");

    // Create a rectangle shape
    sf::RectangleShape rectangle(sf::Vector2f(200.0f, 100.0f));
    rectangle.setPosition(WIDTH / 2.0f, HEIGHT / 2.0f);
    rectangle.setOrigin(100.0f, 50.0f);
    rectangle.setFillColor(sf::Color::Red);

    // Reflection properties
    bool isReflected = false;
    float reflectionPosition = 0.0f;
    float reflectionSpeed = 1.0f;

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

        // Update the reflection position
        if (!isReflected)
        {
            reflectionPosition += reflectionSpeed;
            if (reflectionPosition >= 1.0f)
            {
                reflectionPosition = 1.0f;
                isReflected = true;
            }
        }
        else
        {
            reflectionPosition -= reflectionSpeed;
            if (reflectionPosition <= 0.0f)
            {
                reflectionPosition = 0.0f;
                isReflected = false;
            }
        }

        // Create a reflected rectangle shape
        sf::RectangleShape reflectedRect(rectangle);
        reflectedRect.setPosition(rectangle.getPosition().x, rectangle.getPosition().y + rectangle.getSize().y * reflectionPosition);
        reflectedRect.setScale(1.0f, -1.0f);

        // Draw the original and reflected rectangle
        //window.draw(rectangle);
        window.draw(reflectedRect);

        // Update the window
        window.display();
        sf::sleep(sf::milliseconds(100)); // 60 FPS (1000 ms / 60)
        
    }

    return 0;
}

