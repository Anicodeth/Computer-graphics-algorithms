#include <SFML/Graphics.hpp>

sf::Vector2f calculateBezierPoint(sf::Vector2f P0, sf::Vector2f P1, sf::Vector2f P2, sf::Vector2f P3, float t) {
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    sf::Vector2f point = uuu * P0 + 3 * uu * t * P1 + 3 * u * tt * P2 + ttt * P3;

    return point;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cubic Bezier Curve");
    window.setFramerateLimit(60);

    sf::Vector2f P0(100, 200);
    sf::Vector2f P1(300, 50);
    sf::Vector2f P2(500, 400);
    sf::Vector2f P3(700, 200);

    sf::VertexArray curve(sf::LineStrip);

    for (float t = 0; t <= 1; t += 0.01) {
        sf::Vector2f point = calculateBezierPoint(P0, P1, P2, P3, t);
        curve.append(sf::Vertex(point));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(curve);
        window.display();
    }

    return 0;
}

