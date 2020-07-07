#include "Game.h"

const float Game::playerXSpeed = 100.f;
const float Game::playerYSpeed = 100.f;
const sf::Vector2f Game::startPos = sf::Vector2f(0, 0);
const float Game::zoom = 0.5;
const float Game::zMax = 145;

Game::Game() {
    initWindow();
    initView();
    initTextures();
    initSprites();
}

void Game::resetGame() {
    srand((unsigned)time);

    dead = false;
    initView();
    resetPlayer();

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
    tWallTexture.loadFromFile("assets/wall/1.png");
    enemyTexture.loadFromFile("assets/ennemi/1.png");
}

void Game::initView() {
    viewSpeed = 40.f;
    viewVector = Entity::worldToScreenPositions(sf::Vector2f(0, -1)) * viewSpeed; //R�f�rentiel de la cam�ra
    // Used for initializing view -> called from ctor
    view.reset(sf::FloatRect(0, 0, mWindowsWidth, mWindowsHeight));
    //view.rotate(10.f);
    view.zoom(zoom);
    view.setCenter(startPos);
    mWindow.setView(view);
}

void Game::render(sf::Time elapsedTime) {
    //Used draw elements on screen -> called from run

    mWindow.clear();
    sf::View v = mWindow.getView();
    if (!dead) {
        v.move(viewVector * elapsedTime.asSeconds());
        mWindow.setView(v);
    }

    for (std::shared_ptr<Entity> entity : m_Entities) {
        if(entity->displayable)
            mWindow.draw(entity->sprite);
    }


    //Slider
    sf::RectangleShape slider_sprite(sf::Vector2f(15, player->getWorldPositionZ()));
    slider_sprite.setFillColor(sf::Color::White);
    slider_sprite.setPosition(v.getCenter().x - (mWindowsWidth * zoom) / 2 + 15, v.getCenter().y + (mWindowsHeight * zoom) / 2 - 80 - player->getWorldPositionZ());
    mWindow.draw(slider_sprite);
    mWindow.display();
}

void Game::run() {
    // Loop game location
    srand((unsigned)time);  
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        processEvents();
        if (!dead) {
            updatePlayer(elapsedTime);
            manageEnemy(elapsedTime);
            manageCollisions();
        }
        render(elapsedTime);
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
    if (key == sf::Keyboard::C && pressed) {
        resetGame();
    }
}

sf::Vector2f Game::getScreenPositionFromScreenX(float x) {
    return (sf::Vector2f(viewVector.x * x / 2, viewVector.y * x / 2 + mWindowsHeight - 450));// in world
}

void Game::initSprites() {
    // Used to initialize all sprites -> called from ctor

    for (float wallY = -150; wallY > -1000; wallY -= 150) {
       generateWallAtWorldPositionY(wallY);
    }
    
    // Player
    initPlayer();

    initEnemy();
}

void Game::resetEnemy() {
    enemy->displayable = false;
}

void Game::initEnemy() {
    enemy = std::make_shared<Entity>();
    sf::Sprite sprite;
    sprite.setTexture(enemyTexture);
    enemy->sprite = sprite;
    enemy->type = EntityType::enemy;
    enemy->displayable = false;
    sf::Vector2f worldSize = Entity::screenToWorldPositions(sf::Vector2f(enemyTexture.getSize().x, enemyTexture.getSize().y));
    enemy->size = sf::Vector2u(worldSize.x, worldSize.y);
    m_Entities.push_back(enemy);
}

void Game::initPlayer() {
    player = std::make_shared<Entity>();
    sf::Sprite mPlayer;
    mPlayer.setTexture(playerTexture);
    player->sprite = mPlayer;
    player->type = EntityType::player;
    sf::Vector2f worldSize = Entity::screenToWorldPositions(sf::Vector2f(playerTexture.getSize().x, playerTexture.getSize().y));
    player->size = sf::Vector2u(worldSize.x, worldSize.y);
    m_Entities.push_back(player);
    resetPlayer();
}

void Game::resetPlayer() {
    player->displayable = true;
    player->setWorldPosition(Entity::screenToWorldPositions(startPos));
    player->setWorldZ(0);
}

void Game::generateWallAtWorldPositionY(float y) {
    // 18 y 28 x
    // x = 25.5 + 2*30  / 4
    // y = 8.5
    // z = 16
    sf::Vector2f wallScreenDimensions(28, 30);
    int holePosX = rand() % 9;


    sf::Vector2f wallWorldDimensions = Entity::screenToWorldPositions(wallScreenDimensions);
    sf::Vector2f wallSpotWorld = sf::Vector2f(0, y);
    for (int column = 0; column < 10; column++) {
        for (int line = 10; line > 0; line--) {
            if (line == 1 && column <= holePosX + 2 && column > holePosX)
                continue;
            sf::Sprite wall;

            wall.setTexture(tWallTexture);
            std::shared_ptr<Entity> e_wall = std::make_shared<Entity>();
            e_wall->sprite = wall;
            e_wall->type = EntityType::block;
            e_wall->displayable = true;
            e_wall->size = sf::Vector2u(wallWorldDimensions.x, wallWorldDimensions.y);
            e_wall->setWorldPosition( sf::Vector2f(
                wallSpotWorld.x + (wallWorldDimensions.x - 11) * column,
                wallSpotWorld.y
            ));
            e_wall->column = column;
            e_wall->line = line;
            e_wall->setWorldZ(16 * (10 - line));
            m_Entities.push_back(e_wall);
        }
    }
}

void Game::manageEnemy(sf::Time elapsedTime) {
    if (enemy->displayable) {
        sf::Vector2f vecPos = player->getWorldPosition();
        enemy->setWorldPosition(sf::Vector2f(vecPos.x, enemy->getWorldPosition().y  + 2 * elapsedTime.asSeconds()));
        enemy->setWorldZ(player->getWorldPositionZ());
    }
    else {
        int random = rand() % 9;
        if (random == 0) {
            std::cout << "caca" << std::endl;
            enemy->displayable = true;
            enemy->setWorldPosition(sf::Vector2f(player->getWorldPosition().x, player->getWorldPosition().y - 200));
            enemy->setWorldZ(player->getWorldPositionZ());
        }
    }

}

void Game::updatePlayer(sf::Time elapsedTime) {
    // Used for update all sprites states -> called from run
    sf::Vector2f movement = Entity::screenToWorldPositions(viewVector);
    // sf::Vector2f movement = Entity::screenToWorldPositions(sf::Vector2f(0,0));
    if (playerIsMovingUp && playerIsMovingLeft) {
        if (player->getWorldPositionZ() < zMax)
        player->setWorldZ(player->getWorldPositionZ() + playerXSpeed * elapsedTime.asSeconds());
    }
    else if (playerIsMovingDown && playerIsMovingRight) {
        if(player->getWorldPositionZ() > 0)
            player->setWorldZ(player->getWorldPositionZ() - playerXSpeed * elapsedTime.asSeconds());
    } else {
        if (playerIsMovingUp) {
            // && getScreenPositionFromScreenX(Entity::worldToScreenPositions(player->getWorldPosition).x).y < 
            movement.y -= playerYSpeed;
        }
        if (playerIsMovingDown)
            movement.y += playerYSpeed;
        if (playerIsMovingLeft && player->getWorldPosition().x > 0) {
            movement.x -= playerXSpeed;
        }
        if (playerIsMovingRight && player->getWorldPosition().x < (Entity::screenToWorldPositions(sf::Vector2f(28, 30)).x - 12) * 10) {
            movement.x += playerXSpeed;
        }
    }
    sf::Vector2f playerPos = player->getWorldPosition();
    player->setWorldPosition(player->getWorldPosition() + (movement * elapsedTime.asSeconds()));
}

void Game::manageCollisions() {

    sf::Vector2f playerPos = player->getWorldPosition();
    sf::Vector2f playerPosEnd = playerPos + sf::Vector2f(player->size.x, player->size.y);
    float playerHeight = std::abs(playerPosEnd.y - playerPos.y);
    float playerWidth = std::abs(playerPosEnd.x - playerPos.x);

    for (std::shared_ptr<Entity> entity : m_Entities) {
        if (entity->type == EntityType::player)
            continue;
        sf::Vector2f dims = Entity::screenToWorldPositions(sf::Vector2f(0, 8.5));
        sf::Vector2f entityPos = entity->getWorldPosition();
        if (entity->sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()) &&
            entityPos.y >= playerPos.y && entityPos.y - dims.y <= playerPos.y) {

            sf::Vector2f entityPosEnd = entityPos + sf::Vector2f(entity->size.x, entity->size.y);
            float entityHeight = std::abs(entityPosEnd.y - entityPos.y);
            float entityWidth = std::abs(entityPosEnd.x - entityPos.x);

            if (entityPos.x <= playerPos.x + playerWidth / 2 &&
                entityPos.x + playerWidth / 2 >= playerPos.x &&
                player->getWorldPositionZ() >= entity->getWorldPositionZ() &&
                player->getWorldPositionZ() <= entity->getWorldPositionZ() + 16) {
                if (entity->type == EntityType::block) {
                    viewSpeed = 0.f;
                    dead = true;
                }
                else if (entity->type == EntityType::enemy) {
                    entity->displayable = false;
                }
            }
            // std::cout << " Player = (" << player->getWorldPosition().x << ", " << player->getWorldPosition().y << ", " << player->getWorldPositionZ() << ")" << std::endl;
            // std::cout << " Wall = (" << entity->getWorldPosition().x << ", " << entity->getWorldPosition().y << ", " << entity->getWorldPositionZ() << ")" << std::endl;
            // std::cout << " WallPos = (" << entity->line << ", " << entity->column << ")" << std::endl;
        }
    }
}

Game::~Game() {

}