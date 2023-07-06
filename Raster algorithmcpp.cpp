#include <SFML/Graphics.hpp>

int main() {
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Rasterization");
    window.setFramerateLimit(60);

    // Create a vertex array to store the triangle vertices
    sf::VertexArray triangle(sf::Triangles, 3);

    // Set the positions and colors of the triangle vertices
    triangle[0].position = sf::Vector2f(200, 50);
    triangle[0].color = sf::Color::Red;
    triangle[1].position = sf::Vector2f(400, 400);
    triangle[1].color = sf::Color::Green;
    triangle[2].position = sf::Vector2f(600, 100);
    triangle[2].color = sf::Color::Blue;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Perform the rasterization process
        for (int y = 0; y < window.getSize().y; ++y) {
            for (int x = 0; x < window.getSize().x; ++x) {
                // Check if the pixel is inside the triangle using barycentric coordinates
                sf::Vector2f pixel(x, y);
                sf::Vector2f v0 = triangle[0].position;
                sf::Vector2f v1 = triangle[1].position;
                sf::Vector2f v2 = triangle[2].position;
                float area = 0.5f * (-v1.y * v2.x + v0.y * (-v1.x + v2.x) + v0.x * (v1.y - v2.y) + v1.x * v2.y);
                float w0 = (0.5f * (-v1.y * v2.x + pixel.y * (v1.x - v2.x) + pixel.x * (v2.y - v1.y) + v1.x * v2.y)) / area;
                float w1 = (0.5f * (v0.y * v2.x - v0.x * v2.y + pixel.x * (v2.y - v0.y) + v0.x * (v0.y - pixel.y))) / area;
                float w2 = (0.5f * (v0.x * v1.y - v0.y * v1.x + pixel.x * (v0.y - v1.y) + v0.y * (v1.x - pixel.x))) / area;

                if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                    // The pixel is inside the triangle, so color it
                    sf::Color color = sf::Color::White;
                    color.r = w0 * triangle[0].color.r + w1 * triangle[1].color.r + w2 * triangle[2].color.r;
                    color.g = w0 * triangle[0].color.g + w1 * triangle[1].color.g + w2 * triangle[2].color.g;
                    color.b = w0 * triangle[0].color.b + w1 * triangle[1].color.b + w2 * triangle[2].color.b;
                    sf::RectangleShape pixelRect(sf::Vector2f(1, 1));
                    pixelRect.setPosition(x, y);
                    pixelRect.setFillColor(color);
                    window.draw(pixelRect);
                }
            }
        }

        window.display();
    }

    return 0;
}

