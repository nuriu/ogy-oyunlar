#include <Scenes/MenuScene.hpp>

MenuScene::MenuScene(const CoreComponents& components)
    : m_Components(components)
    , m_Title(std::make_unique<sf::Text>())
    , m_Start(std::make_unique<sf::Text>())
    , m_HighScores(std::make_unique<sf::Text>())
    , m_MenuSelectedIndex(0)
{
}

void MenuScene::initialize()
{
    m_Components.m_AssetManager->loadFont("kenney-high",
                                          "assets/fonts/Kenney-High.ttf");
    m_Components.m_AssetManager->loadSound("click", "assets/sounds/click.wav");
    m_Title->setCharacterSize(100);
    m_Title->setString("Breakout-ish");
    m_Title->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_Title->setPosition(m_Components.m_RenderWindow->getSize().x / 2.f -
                             m_Title->getLocalBounds().width / 2.f,
                         m_Components.m_RenderWindow->getSize().y / 4.f);

    m_Start->setCharacterSize(50);
    m_Start->setString("Start");
    m_Start->setFillColor(sf::Color::Green);
    m_Start->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_Start->setPosition(m_Components.m_RenderWindow->getSize().x / 2.f -
                             m_Start->getLocalBounds().width / 2.f,
                         m_Components.m_RenderWindow->getSize().y / 1.5f);

    m_HighScores->setCharacterSize(50);
    m_HighScores->setString("High Scores");
    m_HighScores->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_HighScores->setPosition(m_Components.m_RenderWindow->getSize().x / 2.f -
                                  m_HighScores->getLocalBounds().width / 2.f,
                              m_Start->getPosition().y +
                                  m_Start->getLocalBounds().height * 2.f);
}

void MenuScene::processInput()
{
    if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Up) ||
        m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Down))
    {
        m_Components.m_AssetManager->playSound("click");

        if (m_MenuSelectedIndex == 0)
        {
            m_MenuSelectedIndex = 1;
            m_Start->setFillColor(sf::Color::White);
            m_HighScores->setFillColor(sf::Color::Green);
        }
        else
        {
            m_MenuSelectedIndex = 0;
            m_Start->setFillColor(sf::Color::Green);
            m_HighScores->setFillColor(sf::Color::White);
        }
    }

    if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Enter))
    {
        if (m_MenuSelectedIndex == 0)
        {
            m_Components.m_SceneManager->pushScene(
                ScenePtr(std::make_unique<PaddleSelectScene>(m_Components)),
                true);
        }
        else
        {
            // TODO: yüksek skorlar sahnesine geç
        }
    }
}

void MenuScene::update() {}

void MenuScene::render() const
{
    m_Components.m_RenderWindow->draw(*m_Title);
    m_Components.m_RenderWindow->draw(*m_Start);
    m_Components.m_RenderWindow->draw(*m_HighScores);
}
