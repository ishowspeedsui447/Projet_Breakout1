#include "Grid.h"
#include "Brick.h"
#include "B_normal.h"
#include "B_dur.h"
#include "B_incassable.h"
#include "Ball.h"

Grid::Grid() {
 
    //float gridWidth = 800;
    //float gridHeight = 400;

    //border.setSize(sf::Vector2f(gridWidth, gridHeight));
    //border.setPosition(10, 20);
    //border.setOutlineThickness(5);
    //border.setFillColor(sf::Color::Transparent);
    //border.setOutlineColor(sf::Color::Red);

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

            // Si la brique n'est pas détruite et qu'il y a collision
            if (!bricks[i][j]->isDestroyed() &&
                ball.getBounds().intersects(bricks[i][j]->getBounds()))
            {
                // On enregistre le coup porté à la brique
                bricks[i][j]->hit();

                // On fait rebondir la balle dans tous les cas
                ball.bondY();

                // CONDITION : On n'ajoute des points que si la brique N'EST PAS incassable
                if (!bricks[i][j]->isUnbreakable()) {
                    score += 10;
                }

                // On retourne le score (soit 10, soit 0 si c'était une incassable)
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

            // On utilise le point '.' car 'bricks[i][j]' est un objet, pas un pointeur
            if (!bricks[i][j]->isDestroyed()) {

                // On vérifie si elle est cassable
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
    /*window.draw(border);*/

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (!bricks[i][j]->isDestroyed()) {
                bricks[i][j]->draw(window);
            }
        }
    }
}