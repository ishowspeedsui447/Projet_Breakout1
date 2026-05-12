#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "grid.h"
#include "Menu.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include <iostream>

class Game {
private:
    RenderWindow window;

    Menu menu;
    Ball ball;
    Paddle paddle;
    Grid grid;

    sf::Clock clock;
    sf::Font font;

    sf::SoundBuffer bufferStart, bufferBrick, bufferPaddle, bufferWall, bufferLostLife;
    sf::Sound soundStart, soundBrick, soundPaddle, soundWall, soundLostLife;

    sf::Music backgroundMusic, menuMusic, endMusic;

    float totalTimeSession = 0.f;
    bool isGameOver;
    bool isWin;
    bool ballLaunched;

    int lives;
    int score;

    // Statistiques
    int highScore;
    int totalGames;

    enum class State { MENU, PLAYING, PAUSE, INSTRUCTIONS, STATS, GAMEOVER};

    State currentState = State::MENU;


public:
    Game();
    ~Game();

    void play();
    void init();

    void chargerSon(sf::SoundBuffer& buffer, sf::Sound& son, const std::string& fichier);
    void handleEvents();
    void update(float dt);
    void handleCollisions();
    void render();

    void resetRound();
    void resetGame();

    void drawText(const std::string& str, float x, float y,
        unsigned size, Color color, bool center = false);
    void drawHUD();
    void drawInstructions();
    void drawStats();
    void drawEndScreen();

    void saveStats();
    void loadStats();
};