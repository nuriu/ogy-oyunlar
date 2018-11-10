#include <Scenes/PaddleSelectScene.hpp>

PaddleSelectScene::PaddleSelectScene(const CoreComponents& components)
    : m_Components(components),
      m_Title(std::make_unique<sf::Text>()),
      m_LeftArrow(std::make_unique<sf::Text>()),
      m_RightArrow(std::make_unique<sf::Text>()),
      m_SelectedPaddleIndex(0) { }

void PaddleSelectScene::initialize()
{
    m_Components.m_AssetManager->loadTexture("paddles",
            "assets/spritesheets/paddles.png");
    m_Components.m_AssetManager->loadTexture("paddles-long",
            "assets/spritesheets/paddles-long.png");
    m_Components.m_AssetManager->loadSound("select",
                                           "assets/sounds/select.wav");

    for(int i = 0; i < 6; ++i)
    {
        if (i < 3)
        {
            m_Paddles.push_back(
                sf::Sprite(m_Components.m_AssetManager->getTexture("paddles"),
                           sf::IntRect(0, i * 30, 125, 30))
            );
        }
        else
        {
            m_Paddles.push_back(
                sf::Sprite(m_Components.m_AssetManager->getTexture("paddles-long"),
                           sf::IntRect(0, (i - 3) * 30, 155, 30))
            );
        }

        m_Paddles[i].setOrigin(m_Paddles[i].getLocalBounds().width / 2.f,
                               m_Paddles[i].getLocalBounds().height / 2.f);
        m_Paddles[i].setPosition(m_Components.m_RenderWindow->getSize().x / 2.f,
                                 m_Components.m_RenderWindow->getSize().y / 1.5f);
    }

    m_Title->setCharacterSize(72);
    m_Title->setString("Select a paddle to start!");
    m_Title->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_Title->setPosition(m_Components.m_RenderWindow->getSize().x / 2.f -
                         m_Title->getLocalBounds().width / 2.f,
                         m_Components.m_RenderWindow->getSize().y / 4.f);

    m_LeftArrow->setCharacterSize(100);
    m_LeftArrow->setString("<");
    m_LeftArrow->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_LeftArrow->setPosition(144 - m_LeftArrow->getLocalBounds().width / 2.f,
                             m_Components.m_RenderWindow->getSize().y / 1.75f -
                             m_LeftArrow->getLocalBounds().height / 2.f);

    m_RightArrow->setCharacterSize(100);
    m_RightArrow->setString(">");
    m_RightArrow->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_RightArrow->setPosition(m_Components.m_RenderWindow->getSize().x - 144 -
                              m_RightArrow->getLocalBounds().width / 2.f,
                              m_Components.m_RenderWindow->getSize().y / 1.75f -
                              m_RightArrow->getLocalBounds().height / 2.f);
}

void PaddleSelectScene::processInput()
{
    if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Left))
    {
        m_Components.m_AssetManager->playSound("click");

        if (--m_SelectedPaddleIndex == -1)
        {
            m_SelectedPaddleIndex = m_Paddles.size() - 1;
        }
    }
    else if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Right))
    {
        m_Components.m_AssetManager->playSound("click");

        if (++m_SelectedPaddleIndex == m_Paddles.size())
        {
            m_SelectedPaddleIndex = 0;
        }
    }
    else if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Enter))
    {
        m_Components.m_AssetManager->playSound("select");
        m_Components.m_SceneManager->pushScene(
            ScenePtr(std::make_unique<PlayScene>(m_Components,
                        m_Paddles[m_SelectedPaddleIndex])), true
        );
    }
}

void PaddleSelectScene::update()
{
}

void PaddleSelectScene::render() const
{
    m_Components.m_RenderWindow->draw(*m_Title);
    m_Components.m_RenderWindow->draw(*m_LeftArrow);
    m_Components.m_RenderWindow->draw(*m_RightArrow);
    m_Components.m_RenderWindow->draw(m_Paddles[m_SelectedPaddleIndex]);
}
