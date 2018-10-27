#include "game.hpp"

// #define GAME_FULLSCREEN

Game::Game(const sf::String &title, const unsigned int width,
           const unsigned int height)
{
#ifdef GAME_FULLSCREEN
    auto desktop = sf::VideoMode::getDesktopMode();
    auto windowMode = sf::VideoMode(desktop.width, desktop.height,
                                    desktop.bitsPerPixel);
    m_Window = std::make_unique<sf::RenderWindow>(windowMode, title,
                                                  sf::Style::Fullscreen);
#else
    m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height),
                                                  title);
#endif

    m_Window->setVerticalSyncEnabled(true);

    m_PlayerOne = std::make_unique<Paddle>(
        sf::Vector2f(10, 100),
        sf::Vector2f(10, m_Window->getSize().y / 2 - 50),
        sf::Color::Magenta);

    m_PlayerTwo = std::make_unique<Paddle>(
        sf::Vector2f(10, 100),
        sf::Vector2f(m_Window->getSize().x - 20,
                     m_Window->getSize().y / 2 - 50),
        sf::Color::Cyan);
}

void Game::run()
{
    while (m_Window->isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_Window->pollEvent(event))
    {
        if ((event.type == sf::Event::Closed) ||
            ((event.type == sf::Event::KeyPressed) &&
             (event.key.code == sf::Keyboard::Escape)))
        {
            m_Window->close();
            break;
        }
    }
}

void Game::update()
{
    float deltaTime = m_Clock.restart().asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
        m_PlayerOne->getPosition().y > 0.f)
    {
        m_PlayerOne->move(0.f, -paddleSpeed * deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        m_PlayerOne->getPosition().y + m_PlayerOne->getSize().y < m_Window->getSize().y)
    {
        m_PlayerOne->move(0.f, paddleSpeed * deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        m_PlayerTwo->getPosition().y > 0.f)
    {
        m_PlayerTwo->move(0.f, -paddleSpeed * deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        m_PlayerTwo->getPosition().y + m_PlayerTwo->getSize().y < m_Window->getSize().y)
    {
        m_PlayerTwo->move(0.f, paddleSpeed * deltaTime);
    }
}

void Game::render()
{
    m_Window->clear();
    m_Window->draw(*m_PlayerOne);
    m_Window->draw(*m_PlayerTwo);
    m_Window->display();
}
