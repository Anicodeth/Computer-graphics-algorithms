#include <SFML/Graphics.hpp>

void bresenhamAlgorithm(sf::RenderWindow& window, int x1, int y1, int x2, int y2) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int error = dx - dy;

    while (x1 != x2 || y1 != y2) {
        sf::RectangleShape pixel(sf::Vector2f(1, 1));
        pixel.setPosition(x1, y1);
        window.draw(pixel);

        int error2 = 2 * error;

        if (error2 > -dy) {
            error -= dy;
            x1 += sx;
        }

        if (error2 < dx) {
            error += dx;
            y1 += sy;
        }
    }

    window.display();
}

int main() {
    int x1 = 50, y1 = 100;
    int x2 = 200, y2 = 250;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Bresenham's Line Algorithm using SFML");
    window.clear();

    bresenhamAlgorithm(window, x1, y1, x2, y2);

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

