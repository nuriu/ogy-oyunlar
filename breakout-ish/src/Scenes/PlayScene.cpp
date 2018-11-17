#include <Scenes/PlayScene.hpp>

PlayScene::PlayScene(const CoreComponents& components, const unsigned int selectedPaddleIndex)
    : m_Components(components)
    , m_Player(std::make_unique<Paddle>(m_Components, selectedPaddleIndex))
    , m_Ball(std::make_unique<Ball>(m_Components))
    , m_RandomDevice()
    , m_MTGenerator(m_RandomDevice())
    , m_Distributor(30.0f, 60.0f)
{
}

void PlayScene::initialize()
{
    m_Components.m_AssetManager->loadTexture("balls", "spritesheets/balls.png");
    m_Components.m_AssetManager->loadTexture("bricks", "spritesheets/bricks.png");
    m_Components.m_AssetManager->loadSound("impact", "sounds/impact.wav");

    m_Player->initialize();
    m_Ball->initialize();

    for (unsigned int row = 0; row < 5; ++row)
    {
        for (unsigned int col = 0; col < 12; ++col)
        {
            m_Bricks.emplace_back(
                std::make_unique<Brick>(m_Components, col * 64.0f + 64.0f, row * 30.f + 30.f));
            m_Bricks.back()->initialize();
        }
    }
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
            else if (m_Ball->getY() + m_Ball->m_Height <= brick.getY()) // üst kenar
            {
                m_Ball->m_DeltaY = -m_Ball->m_DeltaY;
            }
            else // alt kenar
            {
                m_Ball->m_DeltaY = -m_Ball->m_DeltaY;
            }

            m_Ball->m_DeltaY *= 1.025f;

            m_Bricks.erase(m_Bricks.begin() + i);
            m_Components.m_AssetManager->playSound("impact");

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
    }
}

void PlayScene::render() const
{
    m_Player->render();
    m_Ball->render();

    for (auto& brick : m_Bricks)
    {
        brick->render();
    }
}
