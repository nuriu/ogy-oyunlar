#include <Scenes/PlayScene.hpp>

PlayScene::PlayScene(const CoreComponents& components, const unsigned int selectedPaddleIndex)
    : m_Components(components)
    , m_Player(std::make_unique<Paddle>(m_Components, selectedPaddleIndex))
    , m_Ball(std::make_unique<Ball>(m_Components))
{
}

void PlayScene::initialize()
{
    m_Components.m_AssetManager->loadTexture("balls", "spritesheets/balls.png");

    m_Player->initialize();
    m_Ball->initialize();
}

void PlayScene::processInput()
{
    m_Player->processInput();
    m_Ball->processInput();
}

void PlayScene::update()
{
    m_Player->update();
    m_Ball->update();
}

void PlayScene::render() const
{
    m_Player->render();
    m_Ball->render();
}
