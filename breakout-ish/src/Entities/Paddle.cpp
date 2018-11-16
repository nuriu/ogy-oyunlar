#include <Entities/Paddle.hpp>

Paddle::Paddle(const CoreComponents& components, const unsigned int selectedPaddleIndex)
    : m_Components(components), m_PaddleSpeed(1500.f)
{
    if (selectedPaddleIndex < 3)
    {
        setTexture(m_Components.m_AssetManager->getTexture("paddles"));
        setTextureRect(sf::IntRect(0, selectedPaddleIndex * 30, 125, 30));
    }
    else
    {
        setTexture(m_Components.m_AssetManager->getTexture("paddles-long"));
        setTextureRect(sf::IntRect(0, (selectedPaddleIndex - 3) * 30, 155, 30));
    }
}

void Paddle::initialize()
{
    setOrigin(getLocalBounds().width / 2.0f, getLocalBounds().height / 2.0f);
    setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f,
                m_Components.m_RenderWindow->getSize().y - 50.0f);

    m_Width  = getLocalBounds().width;
    m_Height = getLocalBounds().height;
}

void Paddle::processInput()
{
    if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Left))
    {
        if (getPosition().x - m_Width / 2.0f > 10.0f)
        {
            move(m_PaddleSpeed * m_Components.m_TimePerFrame->asSeconds() * -1.0f, 0.0f);
        }
    }
    else if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Right))
    {
        if (getPosition().x + m_Width / 2.0f < m_Components.m_RenderWindow->getSize().x - 10.0f)
        {
            move(m_PaddleSpeed * m_Components.m_TimePerFrame->asSeconds(), 0.0f);
        }
    }
}

void Paddle::update() {}

void Paddle::render() const
{
    m_Components.m_RenderWindow->draw(*this);
}
