#include <SFML/Graphics.hpp>
#include <math.h>

int main()
{
    // Window size
    const int WIDTH = 800;
    const int HEIGHT = 600;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Rotation Example");

    // Create a rectangle shape
    sf::RectangleShape rectangle(sf::Vector2f(200.0f, 100.0f));
    rectangle.setPosition(WIDTH / 2.0f, HEIGHT / 2.0f);
    rectangle.setOrigin(100.0f, 50.0f);
    rectangle.setFillColor(sf::Color::Red);

    // Rotation properties
    bool isRotating = true;
    float rotationAngle = 0.0f;
    float rotationSpeed = 90.0f; // Degrees per second
    sf::Clock timer;
    const float animationDuration = 3.0f;

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

        // Check if the animation duration has passed
        if (timer.getElapsedTime().asSeconds() >= animationDuration)
        {
            timer.restart();
            isRotating = !isRotating;
        }

        // Update the rotation angle
        if (isRotating)
        {
            float rotationAmount = rotationSpeed * timer.getElapsedTime().asSeconds();
            rotationAngle = fmod(rotationAmount, 360.0f);
        }

        // Rotate the rectangle
        rectangle.setRotation(rotationAngle);

        // Draw the rectangle
        window.draw(rectangle);

        // Update the window
        window.display();
        sf::sleep(sf::milliseconds(40)); // 60 FPS (1000 ms / 60)
    }

    return 0;
}

