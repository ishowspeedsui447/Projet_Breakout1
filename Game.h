#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "Grid.h"
#include "Menu.h"

class Game {
private:
    sf::RenderWindow window;

    Ball ball;
    Paddle paddle;
    Grid grid;

    enum GameState {
        MENU,
        PLAYING,
        END
    };

    GameState state;

    Menu menu;

    bool isRunning;
    bool isGameOver;
    bool isWin;
    bool ballLaunched;

    int lives;
    int score;

    sf::Clock clock;
    sf::Font font;

public:
    Game();

    void init();

    void handleEvents();
    void update(float dt);
    void handleCollisions();
    void render();

    void resetRound();
    void resetGame();

    void drawText(const std::string& str, float x, float y,
        unsigned size, sf::Color color, bool center = false);

    void drawHUD();
    void drawEndScreen();

    void play();
};
