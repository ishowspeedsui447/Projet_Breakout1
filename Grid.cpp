//#include "Grid.h"
//
//// Constructeur : appelle les méthodes d'initialisation
//Grid::Grid()
//{
//    initWindow();
//    initShapes();
//}
//
//// Configure la fenêtre SFML
//void Grid::initWindow()
//{
//    window.create(VideoMode(800, 600), "ZeldaOnCrack");
//    window.setFramerateLimit(60);
//}
//
//// Configure le rectangle jaune
////void Grid::initShapes()
////{
////    rectangle.setPosition(10, 20);
////    rectangle.setSize(Vector2f(780, 560));
////    rectangle.setOutlineColor(Color::Yellow);
////    rectangle.setOutlineThickness(5);
////    rectangle.setFillColor(Color::Transparent); // Pas de remplissage, juste le contour
////}
//
//void Grid::initShapes()
//{
//    border.setPrimitiveType(LineStrip); // Dessine des lignes connectées entre chaque point
//    border.resize(4);                   // 4 points = 3 segments (bas ouvert)
//
//    // Les 4 coins, dans l'ordre : bas-gauche → haut-gauche → haut-droite → bas-droite
//    // On part et on finit en bas, mais on NE FERME PAS (pas de 5e point)
//    border[0].position = Vector2f(10, 580);   // bas-gauche
//    border[1].position = Vector2f(10, 20);    // haut-gauche
//    border[2].position = Vector2f(790, 20);   // haut-droite
//    border[3].position = Vector2f(790, 580);  // bas-droite
//
//    // Couleur jaune pour chaque point
//    border[0].color = Color::Yellow;
//    border[1].color = Color::Yellow;
//    border[2].color = Color::Yellow;
//    border[3].color = Color::Yellow;
//}
//
//// Dessine tout à l'écran (une seule frame ici, sans boucle)
//void Grid::render()
//{
//    window.clear(Color::White);
//    window.draw(border);
//    window.display();
//}
//
//// Boucle principale : affiche et attend
//void Grid::run()
//{
//    //while (window.isOpen())
//    //{
//    //    // Gestion des événements (obligatoire pour que SFML affiche correctement)
//    //    Event event;
//    //    while (window.pollEvent(event))
//    //    {
//    //        if (event.type == Event::Closed)
//    //            window.close();
//    //    }
//    //}
//    render();
//    system("Pause >= 0");
//}

#include "Grid.h"
#include <cstdlib>

Grid::Grid()
{
    initWindow();
    initShapes();
}

void Grid::initWindow()
{
    window.create(VideoMode(800, 600), "ZeldaOnCrack");
    window.setFramerateLimit(60);
}

void Grid::initShapes()
{
    float thickness = 5.f; // ← modifie cette valeur pour changer l'épaisseur

    // Trait du haut : horizontal, toute la largeur
    topWall.setSize(Vector2f(780, thickness));
    topWall.setPosition(15, 10);
    topWall.setFillColor(Color::Yellow);

    // Trait gauche : vertical, toute la hauteur sauf le bas
    leftWall.setSize(Vector2f(thickness, 590));
    leftWall.setPosition(10, 10);
    leftWall.setFillColor(Color::Yellow);

    // Trait droit : vertical, toute la hauteur sauf le bas
    rightWall.setSize(Vector2f(thickness, 590));
    rightWall.setPosition(790, 10);
    rightWall.setFillColor(Color::Yellow);
}

void Grid::render()
{
    window.clear(Color::White);
    window.draw(topWall);
    window.draw(leftWall);
    window.draw(rightWall);
    window.display();
}

void Grid::run()
{
    while (window.isOpen())
    {
        
        render(); // clear + draw + display à chaque frame
    }
}