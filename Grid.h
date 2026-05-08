#pragma once

#include <SFML/Graphics.hpp>

#include "Brick.h"
#include "B_normal.h"
#include "B_dur.h"
#include "B_incassable.h"
#include "Ball.h"

class Grid {
private:

    sf::RectangleShape border;

    static const int ROWS = 5;
    static const int COLS = 10;

    Brick* bricks[ROWS][COLS];

public:

    Grid();
    ~Grid();

    void init();

    void draw(sf::RenderWindow& window);

    int handleCollision(Ball& ball);

    bool isCleared();

    void reset();
};
