#include <SFML/Graphics.hpp>

void ddaAlgorithm(sf::RenderWindow& window, int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(std::abs(dx), std::abs(dy));

    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; ++i) {
        sf::RectangleShape pixel(sf::Vector2f(1, 1));
        pixel.setPosition(x, y);
        window.draw(pixel);

        x += xIncrement;
        y += yIncrement;
    }

    window.display();
}

int main() {
    int x1 = 50, y1 = 100;
    int x2 = 200, y2 = 250;

    sf::RenderWindow window(sf::VideoMode(800, 600), "DDA Algorithm using SFML");
    window.clear();

    ddaAlgorithm(window, x1, y1, x2, y2);

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

