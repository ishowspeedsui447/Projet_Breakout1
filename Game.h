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

	int
		_cptLive,	// le compteur de vie
		_bonus; // le nombre de bonus O ramassé
    sf::Clock clock;
    sf::Font font;

public:
	Game();	 // constructeur, initialise les types primitifs à 0
	~Game(); // destructeur, initialise les types primitifs à 0
	bool isEndGame() const { return _endGame; }
	void initialize(); // initialise le visuel du jeu (rectangle, pion, symbole, etc.)

	void play();	 // la main loop du jeu
	void inputKey(); // la saisie des touches pour le déplacement du bonhomme

	void printInfo(std::ostream& sortie) const;	   // affiche le nb de vie, le nb de déplacements et le nb de gouttes d'eau ramassées
	void printEndGame(std::ostream& sortie) const; // affiche les messages game over et victoire?
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

	// Permet de faire un random du positionnement (x,y) selon le type de symbole et le nombres désirés de symbole
	void placeRandomSymbols(std::string symbolName, int nbCharacters);
	Point newPosition(direction dir);				   // Change la position du pion selon la direction prise
	void afficherVecteurSymbole(std::ostream& sortie); // Affiche le contenu du vecteur de symbole au complet
	bool meetCactus(int indice) const;				   // Vérifie si le pion a rencontré un cactus
	bool meetEau(int indice) const;				   // Vérifie si le pion a rencontré une goutte d'eau
	Point collisionMur(direction dir);				   // Vérifie si le pion a rencontré les bordures du jeu en fonction de la direction
	bool validatePosition(int x, int y); // Vérifie si la position random n’est pas sur la position d’un autre symbole du vecteur
    void drawHUD();
    void drawEndScreen();

    void play();
};
