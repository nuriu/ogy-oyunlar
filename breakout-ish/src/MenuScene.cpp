#include <MenuScene.hpp>

MenuScene::MenuScene(std::shared_ptr<CoreComponents> components)
    : m_Components(std::move(components)),
      m_Shape(std::make_unique<sf::CircleShape>())
{

}

void MenuScene::initialize()
{
    m_Shape->setRadius(100.f);
    m_Shape->setFillColor(sf::Color::Magenta);
    m_Shape->setPosition(
        m_Components->m_RenderWindow->getSize().x / 2.f - m_Shape->getRadius(),
        m_Components->m_RenderWindow->getSize().y / 2.f - m_Shape->getRadius());
}

void MenuScene::processInput()
{
    if (m_Components->m_Event->type == sf::Event::KeyPressed &&
            m_Components->m_InputManager->isKeyPressed(sf::Keyboard::H))
    {
        std::cout << "H is pressed." << std::endl;
    }
}

void MenuScene::update()
{
}

void MenuScene::render() const
{
    m_Components->m_RenderWindow->draw(*m_Shape);
}
