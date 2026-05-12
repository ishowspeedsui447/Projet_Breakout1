#include "Grid.h"

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
            //regle anti encerclement
            if (r == 2) {
                // On regarde la brique au-dessus et celle à gauche
                bool voisinHautIncassable = (i > 0 && bricks[i - 1][j]->isUnbreakable());
                bool voisinGaucheIncassable = (j > 0 && bricks[i][j - 1]->isUnbreakable());

                // Si les deux sont déjà grises, on force celle-ci à être verte ou rouge
                if (voisinHautIncassable && voisinGaucheIncassable) {
                    r = rand() % 2; // r normal ou dur
                }
            }

            if (r == 0) {
                bricks[i][j] = new B_normal(x, y);
            }
            else if (r == 1) {
                bricks[i][j] = new B_dur(x, y);
            }
            else {
                bricks[i][j] = new B_incassable(x, y);
            }
        }
    }
}

int Grid::handleCollision(Ball& ball) {
    int score = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            //vérifie si la brique existe et s'il y a collision
            if (!bricks[i][j]->isDestroyed() && ball.getBounds().intersects(bricks[i][j]->getBounds())) {

                sf::FloatRect briquePos = bricks[i][j]->getBounds();
                sf::Vector2f ballePos = ball.getPosition();

                // Si la balle est bien entre le haut et le bas de la brique, 
                // c'est qu'elle a tapé sur un côté (gauche ou droit)
                if (ballePos.y > briquePos.top && ballePos.y < briquePos.top + briquePos.height) {
                    ball.bondX();
                }
                // Sinon, le haut ou bas
                else {
                    ball.bondY();
                }

                bricks[i][j]->hit();

                if (!bricks[i][j]->isUnbreakable()) {
                    score += 10;
                }

                return score; //sort pour ne pas cogner deux briques d'un coup
            }
        }
    }
    return score;
}

bool Grid::isCleared()
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (!bricks[i][j]->isDestroyed()) {

                // vérifie si elle est cassable
                if (!bricks[i][j]->isUnbreakable()) {
                    return false;
                }
            }
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
            if (!bricks[i][j]->isDestroyed()) {
                bricks[i][j]->draw(window);
            }
        }
    }
}