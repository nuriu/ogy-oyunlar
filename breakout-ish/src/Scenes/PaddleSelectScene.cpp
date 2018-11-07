#include <Scenes/PaddleSelectScene.hpp>

PaddleSelectScene::PaddleSelectScene(std::shared_ptr<CoreComponents> components)
    : m_Components(std::move(components)),
      m_Title(std::make_unique<sf::Text>()),
      m_LeftArrow(std::make_unique<sf::Text>()),
      m_RightArrow(std::make_unique<sf::Text>()),
      m_MenuSelectedIndex(0) { }

void PaddleSelectScene::initialize()
{
    m_Title->setCharacterSize(100);
    m_Title->setString("Select a paddle to start!");
    m_Title->setFont(m_Components->m_AssetManager->getFont("kenney-high"));
    m_Title->setPosition(m_Components->m_RenderWindow->getSize().x / 2.f -
                         m_Title->getLocalBounds().width / 2.f,
                         m_Components->m_RenderWindow->getSize().y / 4.f);

    m_LeftArrow->setCharacterSize(100);
    m_LeftArrow->setString("<");
    m_LeftArrow->setFont(m_Components->m_AssetManager->getFont("kenney-high"));
    m_LeftArrow->setPosition(250, m_Components->m_RenderWindow->getSize().y / 2.f);

    m_RightArrow->setCharacterSize(100);
    m_RightArrow->setString(">");
    m_RightArrow->setFont(m_Components->m_AssetManager->getFont("kenney-high"));
    m_RightArrow->setPosition(m_Components->m_RenderWindow->getSize().x - 250,
                              m_Components->m_RenderWindow->getSize().y / 2.f);

}

void PaddleSelectScene::processInput()
{
    if (m_Components->m_Event->type == sf::Event::KeyPressed)
    {
        if (m_Components->m_InputManager->isKeyPressed(sf::Keyboard::Left) ||
                m_Components->m_InputManager->isKeyPressed(sf::Keyboard::Right))
        {
            m_Components->m_AssetManager->playSound("click");
        }
    }
}

void PaddleSelectScene::update()
{
}

void PaddleSelectScene::render() const
{
    m_Components->m_RenderWindow->clear(sf::Color(35, 50, 60));
    m_Components->m_RenderWindow->draw(*m_Title);
    m_Components->m_RenderWindow->draw(*m_LeftArrow);
    m_Components->m_RenderWindow->draw(*m_RightArrow);
}
