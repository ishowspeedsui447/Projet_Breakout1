#include "Menu.h"
using namespace sf;
using namespace std;

Menu::Menu() {
    font.loadFromFile("ARIAL.TTF");

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

    // Bouton Instructions
    instructions.setFont(font);
    instructions.setString("  Instructions  ");
    instructions.setCharacterSize(30);
    instructions.setPosition(220.f, 260.f);
    instructions.setFillColor(Color::Green);

    // Bouton Statistiques
    stats.setFont(font);
    stats.setString("  Statistiques  ");
    stats.setCharacterSize(30);
    stats.setPosition(220.f, 340.f);
    stats.setFillColor(Color::Green);

    // Bouton Quitter
    quit.setFont(font);
    quit.setString("  Quitter  ");
    quit.setCharacterSize(30);
    quit.setPosition(220.f, 420.f);
    quit.setFillColor(Color::Red);

    // Enregistrer les zones cliquables après positionnement
    playBounds = play.getGlobalBounds();
    instructionsBounds = instructions.getGlobalBounds();
    statsBounds = stats.getGlobalBounds();
    quitBounds = quit.getGlobalBounds();
}

Menu::Action Menu::handleEvent(RenderWindow& window, Event& event) {
    Vector2f mousePos;

    if (event.type == Event::MouseMoved) {
        mousePos = Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y);

        play.setFillColor(Color::Green);
        instructions.setFillColor(Color::Green);
        stats.setFillColor(Color::Green);
        quit.setFillColor(Color::Red);

        if (playBounds.contains(mousePos)) {
            play.setFillColor(Color::White);
        }
        else if (instructionsBounds.contains(mousePos)) {
            instructions.setFillColor(Color::White);
        }
        else if (statsBounds.contains(mousePos)) {
            stats.setFillColor(Color::White);
        }
        else if (quitBounds.contains(mousePos)) {
            quit.setFillColor(Color::White);
        }
    }

    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        mousePos = Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y);

        if (playBounds.contains(mousePos)) { return Action::Play; }
        if (instructionsBounds.contains(mousePos)) { return Action::Instructions; }
        if (statsBounds.contains(mousePos)) { return Action::Stats; }
        if (quitBounds.contains(mousePos)) { return Action::Quit; }
    }

    return Action::None;
}

void Menu::draw(RenderWindow& window) {
    window.draw(title);
    window.draw(play);
    window.draw(instructions);
    window.draw(stats);
    window.draw(quit);
}
