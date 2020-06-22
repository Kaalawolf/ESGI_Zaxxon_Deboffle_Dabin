#include "Game.h"

const float Game::playerXSpeed = 100.f;
const float Game::playerYSpeed = 50.f;
const float Game::viewSpeed = .5f;

Game::Game() {
    initWindow();
    initView();
    initTextures();
    initSprites();
}

void Game::initWindow() {
    // Used for initializing window -> called from ctor
    mWindow.create(sf::VideoMode(mWindowsWidth, mWindowsHeight), gameTitle, sf::Style::Close);
    mWindow.setFramerateLimit(60);
    mWindow.setPosition(sf::Vector2i(0, 0));
}

void Game::initTextures() {
    // Used for loading texture files from assets -> called from ctor
    playerTexture.loadFromFile("assets/ship/1.png");
}

void Game::initView() {
    // Used for initializing view -> called from ctor
    view.reset(sf::FloatRect(0, 0, 800, 600));
    view.rotate(10.f);
    mWindow.setView(view);
}

void Game::render() {
    //Used draw elements on screen -> called from run

    mWindow.clear();
    sf::View v = mWindow.getView();
    v.move(sf::Vector2f(viewSpeed, 0.f));
    mWindow.setView(v);

    for (std::shared_ptr<Entity> entity : m_Entities) {
        mWindow.draw(entity->sprite);
    }
    mWindow.display();
}

void Game::run() {
    // Loop game location
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        processEvents();
        update(elapsedTime);
        render();
    }
}

void Game::processEvents() {
    // Used for catch player's inputs -> called from run
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handleInput(event.key.code, true);
            break;

        case sf::Event::KeyReleased:
            handleInput(event.key.code, false);
            break;

        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }

}

void Game::handleInput(sf::Keyboard::Key key, bool pressed) {
    // Used for catch player's inputs -> called from processEvents
    if (key == sf::Keyboard::Up)
        playerIsMovingUp = pressed;
    else if (key == sf::Keyboard::Down)
        playerIsMovingDown = pressed;
    else if (key == sf::Keyboard::Left)
        playerIsMovingLeft = pressed;
    else if (key == sf::Keyboard::Right)
        playerIsMovingRight = pressed;
}

void Game::initSprites() {
    // Used to initialize all sprites -> called from ctor

    // Player
    sf::Sprite mPlayer;
    mPlayer.setTexture(playerTexture);
    mPlayer.setPosition(100.0f, 100.0f);
    player = std::make_shared<Entity>();
    player->sprite = mPlayer;
    player->size = playerTexture.getSize();
    player->position = mPlayer.getPosition();
    m_Entities.push_back(player);

}

void Game::update(sf::Time elapsedTime) {
    // Used for update all sprites states -> called from run
    sf::Vector2f movement(0.f, 0.f);
    if (playerIsMovingUp)
        movement.y -= playerYSpeed;
    if (playerIsMovingDown)
        movement.y += playerYSpeed;
    if (playerIsMovingLeft)
        movement.x -= playerXSpeed;
    if (playerIsMovingRight)
        movement.x += playerXSpeed;

    player->sprite.move(movement * elapsedTime.asSeconds());

}

Game::~Game() {

}