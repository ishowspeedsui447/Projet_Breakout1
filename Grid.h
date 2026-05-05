//
//#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/RectangleShape.hpp>
//
//using namespace sf; // Namespace pour les objets de la librairie SFML
//using namespace std; // Namespace pour les objets de la librairie standard en C++

//#pragma once
//#include <SFML/Graphics.hpp>
//
//using namespace sf;
//
//class Grid
//{
//public:
//    Grid();          // Constructeur : initialise la fenêtre et le rectangle
//    void run();      // Boucle principale du jeu
//
//private:
//    RenderWindow window;       // La fenêtre SFML
//    RectangleShape rectangle;  // Le rectangle à afficher
//    VertexArray border;
//
//    RenderWindow window;
//    RectangleShape topWall;    // trait du haut
//    RectangleShape leftWall;   // trait gauche
//    RectangleShape rightWall;  // trait droit
//
//
//    void initWindow();         // Configure la fenêtre
//    void initShapes();         // Configure le rectangle
//    void render();             // Dessine et affiche tout
//};

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class Grid
{
public:
    Grid();
    void run();

private:
    RenderWindow window;
    RectangleShape topWall;    // trait du haut
    RectangleShape leftWall;   // trait gauche
    RectangleShape rightWall;  // trait droit

    void initWindow();
    void initShapes();
    void render();
};