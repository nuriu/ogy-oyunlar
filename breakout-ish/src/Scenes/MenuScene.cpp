#include <Scenes/MenuScene.hpp>

MenuScene::MenuScene(const CoreComponents& components)
    : m_Components(components)
    , m_Title(std::make_unique<sf::Text>())
    , m_Start(std::make_unique<sf::Text>())
    , m_Exit(std::make_unique<sf::Text>())
    , m_MenuSelectedIndex(0)
{
}

void MenuScene::initialize()
{
    m_Components.m_AssetManager->loadSound("click", "sounds/click.wav");

    m_Title->setCharacterSize(100);
    m_Title->setString("Breakout-ish");
    m_Title->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_Title->setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f -
                             m_Title->getLocalBounds().width / 2.0f,
                         m_Components.m_RenderWindow->getSize().y / 4.f);

    m_Start->setCharacterSize(50);
    m_Start->setString("Start");
    m_Start->setFillColor(sf::Color::Green);
    m_Start->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_Start->setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f -
                             m_Start->getLocalBounds().width / 2.0f,
                         m_Components.m_RenderWindow->getSize().y / 1.5f);

    m_Exit->setCharacterSize(50);
    m_Exit->setString("Exit");
    m_Exit->setFont(m_Components.m_AssetManager->getFont("kenney-high"));
    m_Exit->setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f -
                                  m_Exit->getLocalBounds().width / 2.0f,
                              m_Start->getPosition().y + m_Start->getLocalBounds().height * 2.0f);
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
            m_Exit->setFillColor(sf::Color::Green);
        }
        else
        {
            m_MenuSelectedIndex = 0;
            m_Start->setFillColor(sf::Color::Green);
            m_Exit->setFillColor(sf::Color::White);
        }
    }

    if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Enter))
    {
        if (m_MenuSelectedIndex == 0)
        {
            m_Components.m_SceneManager->pushScene(
                ScenePtr(std::make_unique<PaddleSelectScene>(m_Components)), true);
        }
        else
        {
            m_Components.m_RenderWindow->close();
        }
    }
}

void MenuScene::update() {}

void MenuScene::render() const
{
    m_Components.m_RenderWindow->draw(*m_Title);
    m_Components.m_RenderWindow->draw(*m_Start);
    m_Components.m_RenderWindow->draw(*m_Exit);
}
