#include <SFML/Graphics.hpp>

const int INSIDE = 0; // Bit code for the inside region of the window
const int LEFT = 1;   // Bit code for the left region of the window
const int RIGHT = 2;  // Bit code for the right region of the window
const int BOTTOM = 4; // Bit code for the bottom region of the window
const int TOP = 8;    // Bit code for the top region of the window

// Function to compute the region code for a point (x, y) with respect to the given rectangle
int computeRegionCode(int x, int y, int xmin, int ymin, int xmax, int ymax) {
    int code = INSIDE;

    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;

    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;

    return code;
}

// Function to clip a line segment (x1, y1) to (x2, y2) using Cohen-Sutherland algorithm
void cohenSutherlandLineClip(sf::VertexArray& line, int xmin, int ymin, int xmax, int ymax) {
    int x1 = line[0].position.x;
    int y1 = line[0].position.y;
    int x2 = line[1].position.x;
    int y2 = line[1].position.y;

    int code1 = computeRegionCode(x1, y1, xmin, ymin, xmax, ymax);
    int code2 = computeRegionCode(x2, y2, xmin, ymin, xmax, ymax);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = true;
            break;
        }
        else if (code1 & code2) {
            break;
        }
        else {
            int x, y;

            int codeOut = (code1 != 0) ? code1 : code2;

            // Find the intersection point
            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            // Replace the outside point with the intersection point
            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeRegionCode(x1, y1, xmin, ymin, xmax, ymax);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = computeRegionCode(x2, y2, xmin, ymin, xmax, ymax);
            }
        }
    }

    line[0].position = sf::Vector2f(x1, y1);
    line[1].position = sf::Vector2f(x2, y2);

    if (accept) {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Cohen-Sutherland Line Clipping");
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(line);
            window.display();
        }
    }
}

int main() {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(50, 200);
    line[1].position = sf::Vector2f(500, 50);

    int xmin = 100, ymin = 100, xmax = 400, ymax = 300;
    cohenSutherlandLineClip(line, xmin, ymin, xmax, ymax);

    return 0;
}

