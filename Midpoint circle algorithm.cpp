#include <graphics.h>

void midpointCircleAlgorithm(int centerX, int centerY, int radius) {
    int x = 0;
    int y = radius;
    int decision = 1 - radius;

    while (x <= y) {
        putpixel(centerX + x, centerY + y, WHITE);
        putpixel(centerX - x, centerY + y, WHITE);
        putpixel(centerX + x, centerY - y, WHITE);
        putpixel(centerX - x, centerY - y, WHITE);
        putpixel(centerX + y, centerY + x, WHITE);
        putpixel(centerX - y, centerY + x, WHITE);
        putpixel(centerX + y, centerY - x, WHITE);
        putpixel(centerX - y, centerY - x, WHITE);

        if (decision < 0) {
            decision += 2 * x + 3;
        }
        else {
            decision += 2 * (x - y) + 5;
            y--;
        }

        x++;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int centerX = 300, centerY = 300;
    int radius = 200;

    midpointCircleAlgorithm(centerX, centerY, radius);

    getch();
    closegraph();

    return 0;
}

