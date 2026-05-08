#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "grid.h"

class Game {
private:
    sf::RenderWindow window;

    Ball ball;
    Paddle paddle;
    Grid grid;

    bool isRunning;
    bool isGameOver;
    bool isWin;
    bool ballLaunched;

    int lives;
    int score;

    sf::Clock clock;
    sf::Font font;

    //SONS

    sf::SoundBuffer wallBuffer;
    sf::SoundBuffer paddleBuffer;
    sf::SoundBuffer brickBuffer;
    sf::SoundBuffer hardBrickBuffer;
    sf::SoundBuffer loseBuffer;
    sf::SoundBuffer endGameBuffer;

    sf::Sound wallSound;
    sf::Sound paddleSound;
    sf::Sound brickSound;
    sf::Sound hardBrickSound;
    sf::Sound loseSound;
    sf::Sound endGameSound;

    sf::Music backgroundMusic;
public:
    Game();
    ~Game();

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