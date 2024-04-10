#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Grid dimensions
const int GRID_SIZE = 10;
const int GRID_WIDTH = WIDTH / GRID_SIZE;
const int GRID_HEIGHT = HEIGHT / GRID_SIZE;

// Colors
const sf::Color BLACK = sf::Color::Black;
const sf::Color WHITE = sf::Color::White;
const sf::Color RED = sf::Color::Red;

// Grid
int grid[GRID_WIDTH][GRID_HEIGHT];

// Boundary Fill algorithm with animation
void boundaryFill(sf::RenderWindow& window, int x, int y, sf::Color fillColor, sf::Color borderColor) {
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT && grid[x][y] != fillColor.toInteger() && grid[x][y] != borderColor.toInteger()) {
        grid[x][y] = fillColor.toInteger();
        window.clear(BLACK);

        // Draw the grid
        for (int i = 0; i < GRID_WIDTH; ++i) {
            for (int j = 0; j < GRID_HEIGHT; ++j) {
                sf::RectangleShape cell(sf::Vector2f(GRID_SIZE, GRID_SIZE));
                cell.setPosition(i * GRID_SIZE, j * GRID_SIZE);
                cell.setFillColor(sf::Color(grid[i][j]));
                window.draw(cell);
            }
        }
        window.display();

        // Add delay to visualize the animation
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        boundaryFill(window, x + 1, y, fillColor, borderColor);
        boundaryFill(window, x - 1, y, fillColor, borderColor);
        boundaryFill(window, x, y + 1, fillColor, borderColor);
        boundaryFill(window, x, y - 1, fillColor, borderColor);
    }
}

int main() {
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Boundary Fill");

    // Clear the window to black
    window.clear(BLACK);

    // Initialize the grid with white color
    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            grid[i][j] = WHITE.toInteger();
        }
    }

    int rectX = 3;
    int rectY = 3;
    int rectWidth = 4;
    int rectHeight = 3;

    // Run the program while the window is open
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Perform boundary fill when left mouse button is clicked
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int gridX = mousePos.x / GRID_SIZE;
                int gridY = mousePos.y / GRID_SIZE;
                boundaryFill(window, gridX, gridY, RED, BLACK);
            }
        }
        window.display();
    }
    return 0;
}

