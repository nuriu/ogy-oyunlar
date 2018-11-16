#include <Scenes/PlayScene.hpp>

PlayScene::PlayScene(const CoreComponents& components, const unsigned int selectedPaddleIndex)
    : m_Components(components)
    , m_Player(std::make_unique<Paddle>(m_Components, selectedPaddleIndex))
{
}

void PlayScene::initialize()
{
    m_Player->update();
}

void PlayScene::processInput()
{
    m_Player->processInput();
}

void PlayScene::update()
{
    m_Player->update();
}

void PlayScene::render() const
{
    m_Player->render();
}
