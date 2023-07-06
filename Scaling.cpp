#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main()
{
    // Window size
    const int WIDTH = 800;
    const int HEIGHT = 600;

    // Scaling parameters
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    float scaleSpeed = 0.01f;
    bool scalingUp = true;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Scaling Example");

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

        // Update scaling
        if (scalingUp)
        {
            scaleX += scaleSpeed;
            scaleY += scaleSpeed;
            if (scaleX >= 2.0f)
                scalingUp = false;
        }
        else
        {
            scaleX -= scaleSpeed;
            scaleY -= scaleSpeed;
            if (scaleX <= 1.0f)
                scalingUp = true;
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw a rectangle with scaling
        sf::RectangleShape rectangle(sf::Vector2f(200.0f, 100.0f));
        rectangle.setPosition(WIDTH / 2.0f, HEIGHT / 2.0f);
        rectangle.setOrigin(100.0f, 50.0f);
        rectangle.setScale(scaleX, scaleY);
        rectangle.setFillColor(sf::Color::Red);
        window.draw(rectangle);

        // Update the window
        window.display();

        // Add a delay
        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}

