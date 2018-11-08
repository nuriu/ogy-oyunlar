#include <Scenes/PlayScene.hpp>

PlayScene::PlayScene(const CoreComponents& components, sf::Sprite paddle)
    : m_Components(components),
      m_Paddle(std::make_unique<sf::Sprite>(paddle)) { }

void PlayScene::initialize()
{
    m_Paddle->setPosition(m_Components.m_RenderWindow->getSize().x / 2.f,
                          m_Components.m_RenderWindow->getSize().y / 1.15f);
}

void PlayScene::processInput()
{

}

void PlayScene::update()
{

}

void PlayScene::render() const
{
    m_Components.m_RenderWindow->draw(*m_Paddle);
}
