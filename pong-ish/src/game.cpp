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

    m_Font = std::make_unique<sf::Font>();

    if (!m_Font->loadFromFile("assets/fonts/Kenney-Blocks.ttf"))
    {
        exit(EXIT_FAILURE);
    }

    m_Title = std::make_unique<sf::Text>("Pong-ish", *m_Font);
    m_StatusText = std::make_unique<sf::Text>("Playing", *m_Font);
    m_PlayerOneScoreText = std::make_unique<sf::Text>("0", *m_Font);
    m_PlayerTwoScoreText = std::make_unique<sf::Text>("0", *m_Font);

    m_Title->setFillColor(sf::Color::White);
    m_StatusText->setFillColor(sf::Color::White);
    m_PlayerOneScoreText->setFillColor(sf::Color::White);
    m_PlayerTwoScoreText->setFillColor(sf::Color::White);

    m_Title->setCharacterSize(40.f);
    m_StatusText->setCharacterSize(20.f);
    m_PlayerOneScoreText->setCharacterSize(50.f);
    m_PlayerTwoScoreText->setCharacterSize(50.f);

    m_Title->setPosition(sf::Vector2f(m_Window->getSize().x / 2 - 110, 20));
    m_StatusText->setPosition(sf::Vector2f(m_Window->getSize().x / 2 - 50, 100));
    m_PlayerOneScoreText->setPosition(sf::Vector2f(m_Window->getSize().x / 4 - 20, 150));
    m_PlayerTwoScoreText->setPosition(sf::Vector2f(m_Window->getSize().x / 4 * 3, 150));

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

    m_IsPlaying = true;

    initGameRound();
}

void Game::run()
{
    while (m_Window->isOpen())
    {
        processEvents();

        if (m_IsPlaying)
        {
            update();
        }

        render();
    }
}

void Game::initGameRound()
{
    // oyuncuların ve topun konumlarını varsayılan değerlerine çekiyoruz
    m_PlayerOne->setPosition(sf::Vector2f(10, m_Window->getSize().y / 2 - 50));

    m_PlayerTwo->setPosition(sf::Vector2f(m_Window->getSize().x - 20,
                                          m_Window->getSize().y / 2 - 50));

    m_Ball->setPosition(sf::Vector2f(m_Window->getSize().x / 2 - 5,
                                     m_Window->getSize().y / 2 - 5));

    // topun ilk atışta sahip olacağı açıyı yeniden hesaplıyoruz
    // kaynak: SFML pong örneği "SFML_DIR/examples/pong"
    do
    {
        m_BallAngle = (std::rand() % 360) * 2 * pi / 360;
    } while (std::abs(std::cos(m_BallAngle)) < 0.7f);
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

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
        {
            if (!m_IsPlaying)
            {
                m_IsPlaying = true;

                m_Clock.restart();

                m_PlayerOneScore = 0;
                m_PlayerTwoScore = 0;

                m_PlayerOneScoreText->setString(std::to_string(m_PlayerOneScore));
                m_PlayerTwoScoreText->setString(std::to_string(m_PlayerTwoScore));

                m_StatusText->setString("Playing");
                m_StatusText->setPosition(sf::Vector2f(m_Window->getSize().x / 2 - 50, 100));

                initGameRound();
            }
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

        // ekranın sol sınırını geçme durumu
        // m_PlayerTwo 1 skor puanı alır
        if (m_Ball->getPosition().x < 0.f)
        {
            m_PlayerTwoScore++;
            m_PlayerTwoScoreText->setString(std::to_string(m_PlayerTwoScore));

            if (m_PlayerTwoScore == 10)
            {
                m_StatusText->setString("Player Two Won! Press Space to restart.");
                m_StatusText->setPosition(sf::Vector2f(m_Window->getSize().x / 3 - 25, 100));
                m_IsPlaying = false;
            }

            initGameRound();
        }

        // ekranın sağ sınırını geçme durumu
        // m_PlayerOne 1 skor puanı alır
        if (m_Ball->getPosition().x + m_Ball->getSize().x > m_Window->getSize().x)
        {
            m_PlayerOneScore++;
            m_PlayerOneScoreText->setString(std::to_string(m_PlayerOneScore));

            if (m_PlayerOneScore == 10)
            {
                m_StatusText->setString("Player One Won! Press Space to restart.");
                m_StatusText->setPosition(sf::Vector2f(m_Window->getSize().x / 3 - 25, 100));
                m_IsPlaying = false;
            }

            initGameRound();
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

    if (m_IsPlaying)
    {
        m_Window->draw(*m_PlayerOne);
        m_Window->draw(*m_PlayerTwo);
        m_Window->draw(*m_Ball);
    }

    m_Window->draw(*m_Title);
    m_Window->draw(*m_StatusText);
    m_Window->draw(*m_PlayerOneScoreText);
    m_Window->draw(*m_PlayerTwoScoreText);

    m_Window->display();
}
