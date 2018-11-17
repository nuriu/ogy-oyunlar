#include <Scenes/PlayScene.hpp>

PlayScene::PlayScene(const CoreComponents& components, const unsigned int selectedPaddleIndex)
    : m_Components(components)
    , m_Player(std::make_unique<Paddle>(m_Components, selectedPaddleIndex))
    , m_Ball(std::make_unique<Ball>(m_Components))
    , m_RandomDevice()
    , m_MTGenerator(m_RandomDevice())
    , m_Distributor(100.0f, 150.0f)
    , m_ScoreText(std::make_unique<sf::Text>())
    , m_TitleText(std::make_unique<sf::Text>())
    , m_Health(3)
    , m_IsPlaying(false)
    , m_Score(0)

{
}

void PlayScene::initialize()
{
    m_Components.m_AssetManager->loadTexture("hearts", "spritesheets/hearts.png");
    m_Components.m_AssetManager->loadTexture("balls", "spritesheets/balls.png");
    m_Components.m_AssetManager->loadTexture("bricks", "spritesheets/bricks.png");
    m_Components.m_AssetManager->loadSound("impact", "sounds/impact.wav");
    m_Components.m_AssetManager->loadSound("death", "sounds/death.wav");

    m_Player->initialize();
    m_Ball->initialize();

    for (unsigned int row = 0; row < 5; ++row)
    {
        for (unsigned int col = 0; col < 12; ++col)
        {
            m_Bricks.emplace_back(
                std::make_unique<Brick>(m_Components, col * 64.0f + 64.0f, row * 30.0f + 64.0f));
            m_Bricks.back()->initialize();
        }
    }

    for (unsigned int i = 0; i < 3; ++i)
    {
        m_Hearts.emplace_back(m_Components.m_AssetManager->getTexture("hearts"),
                              sf::IntRect(0, 0, 14, 13));

        m_Hearts.back().setPosition(
            m_Components.m_RenderWindow->getSize().x - 132.0f + (i + 1) * 16, 46.0f);
    }

    m_ScoreText->setCharacterSize(32);
    m_ScoreText->setString("Score: " + std::to_string(m_Score));
    m_ScoreText->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_ScoreText->setPosition(64.0f, 24.0f);

    m_TitleText->setCharacterSize(32);
    m_TitleText->setString("Press Space to Start!");
    m_TitleText->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_TitleText->setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f -
                                 m_TitleText->getLocalBounds().width / 2.0f,
                             24.0f);
}

void PlayScene::processInput()
{
    if (m_IsPlaying)
    {
        m_Player->processInput();
        m_Ball->processInput();
    }
    else
    {
        if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Space))
        {
            m_IsPlaying = !m_IsPlaying;
            m_TitleText->setString("Level: 1");
            m_TitleText->setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f -
                                         m_TitleText->getLocalBounds().width / 2.0f,
                                     24.0f);
        }
    }
}

void PlayScene::update()
{
    if (m_IsPlaying)
    {
        m_Player->update();
        m_Ball->update();

        for (unsigned int i = 0; i < m_Bricks.size(); ++i)
        {
            if (m_Ball->isColliding(*m_Bricks.at(i)))
            {
                const Brick& brick = *m_Bricks.at(i);

                m_Ball->setPosition(
                    m_Ball->getX() + -m_Ball->m_DeltaX * m_Components.m_DeltaTime->asSeconds(),
                    m_Ball->getY() + -m_Ball->m_DeltaY * m_Components.m_DeltaTime->asSeconds());

                // sağa giderken sol kenar ile çarpışma
                if (m_Ball->m_DeltaX > 0.0f and m_Ball->getX() + m_Ball->m_Width <= brick.getX())
                {
                    m_Ball->m_DeltaX = -m_Ball->m_DeltaX;
                }
                else if (m_Ball->getX() >= brick.getX() + brick.m_Width) // sola giderken sağ kenar
                {
                    m_Ball->m_DeltaX = -m_Ball->m_DeltaX;
                }
                else // üst kenar veya alt kenar
                {
                    m_Ball->m_DeltaY = -m_Ball->m_DeltaY;
                }

                m_Ball->m_DeltaY *= 1.025f;

                m_Bricks.erase(m_Bricks.begin() + i);
                m_Components.m_AssetManager->playSound("impact");
                m_Score += 10;
                m_ScoreText->setString("Score: " + std::to_string(m_Score));
                break;
            }
        }

        if (m_Ball->isColliding(*m_Player))
        {
            m_Ball->setPosition(m_Ball->getX(), m_Ball->getY() - m_Player->m_Height / 2.0f);
            m_Ball->m_DeltaY = -m_Ball->m_DeltaY;

            if (m_Ball->m_DeltaX < 0.0f)
            {
                m_Ball->m_DeltaX = -m_Distributor(m_MTGenerator);
            }
            else
            {
                m_Ball->m_DeltaX = m_Distributor(m_MTGenerator);
            }

            m_Components.m_AssetManager->playSound("impact");
        }

        if (m_Ball->getY() > m_Components.m_RenderWindow->getSize().y)
        {
            m_Ball->reset();

            if (--m_Health < 1)
            {
                // TODO: game over
                m_IsPlaying = false;
                m_Player->reset();

                m_TitleText->setString("You lost your all hearts!");
                m_TitleText->setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f -
                                             m_TitleText->getLocalBounds().width / 2.0f,
                                         24.0f);
            }

            m_Hearts.at(static_cast<unsigned long>(m_Health))
                .setTextureRect(sf::IntRect(14, 0, 14, 13));

            m_Components.m_AssetManager->playSound("death");
        }

        if (m_Bricks.size() == 0)
        {
            // TODO: game over

            m_IsPlaying = false;

            m_TitleText->setString("You won!");
            m_TitleText->setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f -
                                         m_TitleText->getLocalBounds().width / 2.0f,
                                     24.0f);
        }
    }
}

void PlayScene::render() const
{
    for (const auto& brick : m_Bricks)
    {
        brick->render();
    }

    m_Ball->render();
    m_Player->render();

    for (const auto& heart : m_Hearts)
    {
        m_Components.m_RenderWindow->draw(heart);
    }

    m_Components.m_RenderWindow->draw(*m_ScoreText);
    m_Components.m_RenderWindow->draw(*m_TitleText);
}
