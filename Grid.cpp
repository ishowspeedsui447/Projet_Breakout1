#include "Grid.h"
#include "B_normal.h"
#include "B_dur.h"
#include "B_incassable.h"
#include "Ball.h"

Grid::Grid() {
    init();
}

Grid::~Grid()
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            delete bricks[i][j];
        }
    }
}

void Grid::init()
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            float x = 60 + j * 70;
            float y = 50 + i * 30;

            int r = rand() % 3;

            if (r == 0)
                bricks[i][j] = new B_normal(x, y);

            else if (r == 1)
                bricks[i][j] = new B_dur(x, y);

            else
                bricks[i][j] = new B_incassable(x, y);
        }
    }
}

int Grid::handleCollision(Ball& ball)
{
    int score = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (!bricks[i][j]->isDestroyed() &&
                ball.getBounds().intersects(bricks[i][j]->getBounds()))
            {
                bricks[i][j]->hit();

                ball.bondY();

                score += 10;

                return score;
            }
        }
    }

    return score;
}

bool Grid::isCleared()
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (!bricks[i][j]->isDestroyed())
                return false;
        }
    }

    return true;
}

void Grid::reset()
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            delete bricks[i][j];
        }
    }

    init();
}

void Grid::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            bricks[i][j]->draw(window);
        }
    }
}