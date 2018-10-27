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

    m_Ball = std::make_unique<Paddle>(
        sf::Vector2f(10, 10),
        sf::Vector2f(m_Window->getSize().x / 2 - 5,
                     m_Window->getSize().y / 2 - 5),
        sf::Color::White);

    std::srand(static_cast<unsigned int>(std::time(NULL)));

    // topun başlangıç açısının belirlenmesi
    // kaynak: SFML pong örneği "SFML_DIR/examples/pong"
    do
    {
        m_BallAngle = (std::rand() % 360) * 2 * pi / 360;
    } while (std::abs(std::cos(m_BallAngle)) < 0.7f);
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

    // paddle hareket güncellemeleri
    {
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

    // top hareket güncellemeleri
    {
        m_Ball->move(std::cos(m_BallAngle) * ballSpeed * deltaTime,
                     std::sin(m_BallAngle) * ballSpeed * deltaTime);

        // ekranın üstüne çarpma durumu
        if (m_Ball->getPosition().y < 0.f)
        {
            m_BallAngle = -m_BallAngle;
            m_Ball->setPosition(m_Ball->getPosition().x,
                                m_Ball->getSize().y + 0.1f);
        }

        // ekranın altına çarpma durumu
        if (m_Ball->getPosition().y + m_Ball->getSize().y > m_Window->getSize().y)
        {
            m_BallAngle = -m_BallAngle;
            m_Ball->setPosition(m_Ball->getPosition().x,
                                m_Window->getSize().y - m_Ball->getSize().y - 0.1f);
        }

        // AABB çarpışma tanılama
        // m_PlayerOne (sol paddle) ile çarpışma durumu
        if (m_Ball->getPosition().x <= m_PlayerOne->getPosition().x + m_PlayerOne->getSize().x &&
            m_Ball->getPosition().x + m_Ball->getSize().x >= m_PlayerOne->getPosition().x &&
            m_Ball->getPosition().y <= m_PlayerOne->getPosition().y + m_PlayerOne->getSize().y &&
            m_Ball->getPosition().y + m_Ball->getSize().y >= m_PlayerOne->getPosition().y)
        {
            // topun çarpışma sonrası yönü
            if (m_Ball->getPosition().y > m_PlayerOne->getPosition().y)
            {
                m_BallAngle = pi - m_BallAngle + (std::rand() % 20) * pi / 180;
            }
            else
            {
                m_BallAngle = pi - m_BallAngle - (std::rand() % 20) * pi / 180;
            }

            m_Ball->setPosition(m_PlayerOne->getPosition().x + m_Ball->getSize().x + 0.1f,
                                m_Ball->getPosition().y);
        }

        // m_PlayerTwo (sağ paddle) ile çarpışma durumu
        if (m_Ball->getPosition().x + m_Ball->getSize().x >= m_PlayerTwo->getPosition().x &&
            m_Ball->getPosition().x + m_Ball->getSize().x <= m_PlayerTwo->getPosition().x + m_PlayerTwo->getSize().x &&
            m_Ball->getPosition().y + m_Ball->getSize().y >= m_PlayerTwo->getPosition().y &&
            m_Ball->getPosition().y <= m_PlayerTwo->getPosition().y + m_PlayerTwo->getSize().y)
        {
            // topun çarpışma sonrası yönü
            if (m_Ball->getPosition().y > m_PlayerTwo->getPosition().y)
            {
                m_BallAngle = pi - m_BallAngle + (std::rand() % 20) * pi / 180;
            }
            else
            {
                m_BallAngle = pi - m_BallAngle - (std::rand() % 20) * pi / 180;
            }

            m_Ball->setPosition(m_PlayerTwo->getPosition().x - m_Ball->getSize().x - 0.1f,
                                m_Ball->getPosition().y);
        }
    }
}

void Game::render()
{
    m_Window->clear();
    m_Window->draw(*m_PlayerOne);
    m_Window->draw(*m_PlayerTwo);
    m_Window->draw(*m_Ball);
    m_Window->display();
}
