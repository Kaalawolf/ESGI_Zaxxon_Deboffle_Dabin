#include "Game.h"

Game::Game()
     {
    initWindow();


    circle.setFillColor(sf::Color(255, 0, 0));
    circle.setRadius(50);
    rect.setSize(sf::Vector2f(45.0f, 45.0f));
    rect.setFillColor(sf::Color::Blue);
    rect.setPosition(sf::Vector2f(45.0f, 45.0f));

    view.reset(sf::FloatRect(0, 0, 800, 600));
    view.rotate(45.f);
    mWindow.setView(view);
    while (mWindow.isOpen()) {
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mWindow.close();
            }
        }
        test++;
        circle.setPosition(test, 100);
        refreshWindow();
    }
}

void Game::initWindow() {
    mWindow.create(sf::VideoMode(mWindowsWidth, mWindowsHeight), gameTitle, sf::Style::Close);
    mWindow.setFramerateLimit(60);
    mWindow.setPosition(sf::Vector2i(0, 0));
}

void Game::refreshWindow() {
    mWindow.clear();
    mWindow.draw(rect);
    mWindow.draw(circle);
    mWindow.display();
}