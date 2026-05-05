//#include "Grid.h"
//#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/RectangleShape.hpp>
//
//using namespace sf; // Namespace pour les objets de la librairie SFML
//using namespace std; // Namespace pour les objets de la librairie standard en C++
//#include<iostream>
//
//int main() {
//
//	/*std::cout << "anthony aime les jeux de mineur ',:| like are we fr bro ? ";*/
//
//
//	RenderWindow window(VideoMode(800, 600), "ZeldaOnCrack");
//	window.setFramerateLimit(60); // un appel suffit, après la création de la fenêtre(pour toutes les modifs)
//
//	RectangleShape rectangle;
//	rectangle.setPosition(10, 20);
//	rectangle.setSize(Vector2f(780, 560));
//	rectangle.setOutlineColor(Color::Yellow);
//	rectangle.setOutlineThickness(5);
//
//	window.clear(Color::Black);
//
//	window.draw(rectangle);
//	window.display(); // fin de la frame courante, affichage de tout ce qu'on a dessiné
//	
//	system("Pause >= 0");
//}

//#include "Grid.h"
//
//int main()
//{
//    Grid Grid;   // Crée le jeu (initialise fenêtre + formes)
//    Grid.run();  // Lance l'affichage
//
//    return 0;
//}

#include "Grid.h"

int main()
{
    Grid Grid;   // Crée le jeu (initialise fenêtre + formes)
    Grid.run();  // Lance l'affichage

    return 0;
}