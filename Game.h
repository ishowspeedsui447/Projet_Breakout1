#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "mesFonctions.h"


class Game {
private:
    bool _lose;
    bool _endGame;

    enum direction {
        STOP,
        LEFT,
        RIGHT,
        NONE
    };
   
    direction _dir;

    int lives;
    float ballSpeed;

    sf::RenderWindow window;
    Ball ball;
    Paddle paddle;
    Brick brick;

public:
    // Construction
    Game();

    // destructeur
    ~Game(); 

    bool isEndGame() const { return _endGame; }
    void initialize(); // initialise le visuel du jeu (grid, briques, socle, etc.)

    void play();	 // la main loop du jeu
    void inputKey(); // la saisie des touches pour le déplacement du socle

    //Commencement
    void printInfo(std::ostream& sortie) const;	   // affiche le nb de vie restant, et le nb de briques restantes
    void printEndGame(std::ostream& sortie) const; // affiche les messages game over et victoire 

    // Logique
    void handleLaunch();
    void restart();

    // Boucle principale
    void handleEvents();
    void update(float dt);
    void render();

    // Affichage
    void drawText(const std::string& str, float x, float y,
        unsigned size, sf::Color color, bool center = false);
    void drawHUD();
    void drawMessage();

};
