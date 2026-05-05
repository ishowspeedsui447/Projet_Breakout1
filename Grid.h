#pragma once
#include "B_normal.h"
#include "B_dur.h"
#include "B_incassable.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>

class Grid {
private:
    static const int ROWS = 5;
    static const int COLS = 10;

    B_normal normal[ROWS][COLS];
    B_dur dur[ROWS][COLS];
    B_incassable incassable[ROWS][COLS];
    int type[ROWS][COLS]; // 0=normal, 1=dur, 2=incassable

public:
    Grid();

    void init();
    void draw(sf::RenderWindow& window);
    int handleCollision(Ball& ball);
    bool isCleared();
    void reset();
};

