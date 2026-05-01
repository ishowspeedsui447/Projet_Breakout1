#include "Menu.h"
using namespace sf;
using namespace std;

Menu::Menu() {
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    // Titre
    title.setFont(font);
    title.setString("BREAKOUT");
    title.setCharacterSize(60);
    title.setPosition(200.f, 50.f);
    title.setFillColor(Color::Yellow);

    // Bouton Jouer
    play.setFont(font);
    play.setString("  Jouer  ");
    play.setCharacterSize(30);
    play.setPosition(220.f, 180.f);
    play.setFillColor(Color::Green);

    // Bouton Quitter
    quit.setFont(font);
    quit.setString("  Quitter  ");
    quit.setCharacterSize(30);
    quit.setPosition(220.f, 260.f);
    quit.setFillColor(Color::Red);

    // Enregistrer les zones cliquables après positionnement
    playBounds = play.getGlobalBounds();
    quitBounds = quit.getGlobalBounds();
}

Menu::Action Menu::handleEvent(RenderWindow& window, Event& event) {

    // Survol de la souris : changer la couleur au survol
    if (event.type == Event::MouseMoved) {
        Vector2f mousePos((float)event.mouseMove.x, (float)event.mouseMove.y);

        if (playBounds.contains(mousePos))
            play.setFillColor(Color::White);
        else
            play.setFillColor(Color::Green);

        if (quitBounds.contains(mousePos))
            quit.setFillColor(Color::White);
        else
            quit.setFillColor(Color::Red);
    }

    // Clic gauche de la souris
    if (event.type == Event::MouseButtonPressed &&
        event.mouseButton.button == Mouse::Left)
    {
        Vector2f mousePos((float)event.mouseButton.x,
            (float)event.mouseButton.y);

        if (playBounds.contains(mousePos))
            return Action::Play;

        if (quitBounds.contains(mousePos))
            return Action::Quit;
    }

    return Action::None;
}

void Menu::draw(RenderWindow& window) {
    window.draw(title);
    window.draw(play);
    window.draw(quit);
}
