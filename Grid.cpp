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

            int t = rand() % 3;
            type[i][j] = t;

            if (t == 0)
                normal[i][j] = B_normal(x, y);
            else if (t == 1)
                dur[i][j] = B_dur(x, y);
            else
                incassable[i][j] = B_incassable(x, y);
        }
    }
}

int Grid::handleCollision(Ball& ball) {


    int score = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (type[i][j] == 0) {
                if (!normal[i][j].isDestroyed() &&
                    ball.getBounds().intersects(normal[i][j].getBounds())) {

                    normal[i][j].hit();
                    ball.bondY();
                    score += 10;
                }
            }
            else if (type[i][j] == 1) {
                if (!dur[i][j].isDestroyed() &&
                    ball.getBounds().intersects(dur[i][j].getBounds())) {

                    dur[i][j].hit();
                    ball.bondY();

                    if (dur[i][j].isDestroyed())
                        score += 20;
                }
            }
            else {
                if (ball.getBounds().intersects(incassable[i][j].getBounds())) {
                    ball.bondY();
                }
            }
        }
    }

    return score;
}

void Grid::draw(sf::RenderWindow& window) {

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (type[i][j] == 0) {
                if (!normal[i][j].isDestroyed())
                    normal[i][j].draw(window);
            }
            else if (type[i][j] == 1) {
                if (!dur[i][j].isDestroyed())
                    dur[i][j].draw(window);
            }
            else {
                incassable[i][j].draw(window);
            }
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