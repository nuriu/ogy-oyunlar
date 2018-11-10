#include <Scenes/PlayScene.hpp>

PlayScene::PlayScene(const CoreComponents& components, sf::Sprite paddle)
    : m_Components(components),
      m_Paddle(std::make_unique<sf::Sprite>(paddle)),
      m_PaddleSpeed(1500.f) { }

void PlayScene::initialize()
{
    m_Paddle->setPosition(m_Components.m_RenderWindow->getSize().x / 2.f,
                          m_Components.m_RenderWindow->getSize().y - 50.f);
}

void PlayScene::processInput()
{
    if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Left) &&
            m_Paddle->getPosition().x - m_Paddle->getLocalBounds().width / 2.f > 10.f)
    {
        m_Paddle->move(m_PaddleSpeed * m_Components.m_TimePerFrame->asSeconds() * -1.f,
                       0.f);
    }
    else if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Right) &&
             m_Paddle->getPosition().x + m_Paddle->getLocalBounds().width / 2.f <
             m_Components.m_RenderWindow->getSize().x - 10.f)
    {
        m_Paddle->move(m_PaddleSpeed * m_Components.m_TimePerFrame->asSeconds(), 0.f);
    }
}

void PlayScene::update()
{

}

void PlayScene::render() const
{
    m_Components.m_RenderWindow->draw(*m_Paddle);
}
