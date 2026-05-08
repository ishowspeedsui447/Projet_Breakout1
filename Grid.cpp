#include "Grid.h"
#include "B_normal.h"
#include "B_dur.h"
#include "B_incassable.h"
#include "Ball.h"

Grid::Grid() {
    init();
}

void Grid::init() {

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            float x = 60 + j * 70;
            float y = 50 + i * 30;

            normal[i][j] = B_normal(x, y);
            dur[i][j] = B_dur(x, y);
            incassable[i][j] = B_incassable(x, y);
        }
    }
}

int Grid::handleCollision(Ball& ball) {

    int score = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            // ligne 0 = incassable
            if (i == 0) {
                if (ball.getBounds().intersects(incassable[i][j].getBounds())) {
                    incassable[i][j].hit();
                    ball.bondY();
                }
            }

            // ligne 1 = dur
            else if (i == 1) {
                if (ball.getBounds().intersects(dur[i][j].getBounds())) {
                    dur[i][j].hit();
                    ball.bondY();

                    if (dur[i][j].isDestroyed())
                        score += 20;
                }
            }

            // reste = normal
            else {
                if (ball.getBounds().intersects(normal[i][j].getBounds())) {
                    normal[i][j].hit();
                    ball.bondY();

                    if (normal[i][j].isDestroyed())
                        score += 10;
                }
            }
        }
    }

    return score;
}

void Grid::draw(sf::RenderWindow& window) {

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (i == 0)
                incassable[i][j].draw(window);
            else if (i == 1)
                dur[i][j].draw(window);
            else
                normal[i][j].draw(window);
        }
    }
}

bool Grid::isCleared() {

    for (int i = 1; i < ROWS; i++) { // ignore incassable
        for (int j = 0; j < COLS; j++) {

            if (i == 1 && !dur[i][j].isDestroyed())
                return false;

            if (i > 1 && !normal[i][j].isDestroyed())
                return false;
        }
    }

    return true;
}