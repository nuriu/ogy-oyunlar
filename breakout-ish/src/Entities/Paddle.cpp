#include <Entities/Paddle.hpp>

Paddle::Paddle(const CoreComponents& components, const unsigned int selectedPaddleIndex)
    : m_DeltaX(0.0f), m_Width(0.0f), m_Height(0.0f), m_Components(components), m_PaddleSpeed(1500.f)
{
    if (selectedPaddleIndex < 3)
    {
        this->setTexture(m_Components.m_AssetManager->getTexture("paddles"));
        this->setTextureRect(sf::IntRect(0, selectedPaddleIndex * 24, 100, 24));
    }
    else
    {
        this->setTexture(m_Components.m_AssetManager->getTexture("paddles-long"));
        this->setTextureRect(sf::IntRect(0, (selectedPaddleIndex - 3) * 24, 124, 24));
    }
}

void Paddle::initialize()
{
    this->setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f -
                          this->getLocalBounds().width / 2.0f,
                      m_Components.m_RenderWindow->getSize().y - 25.0f);

    m_Width  = this->getLocalBounds().width;
    m_Height = this->getLocalBounds().height;
}

void Paddle::processInput()
{
    if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Left))
    {
        m_DeltaX = m_PaddleSpeed * m_Components.m_DeltaTime->asSeconds() * -1.0f;

        if (this->getPosition().x > 10.0f)
        {
            this->move(m_DeltaX, 0.0f);
        }
    }
    else if (m_Components.m_InputManager->isKeyPressed(sf::Keyboard::Right))
    {
        m_DeltaX = m_PaddleSpeed * m_Components.m_DeltaTime->asSeconds();

        if (this->getPosition().x + m_Width < m_Components.m_RenderWindow->getSize().x - 10.0f)
        {
            this->move(m_DeltaX, 0.0f);
        }
    }
}

void Paddle::update() {}

void Paddle::render() const
{
    m_Components.m_RenderWindow->draw(*this);
}

float Paddle::getX() const
{
    return this->getPosition().x;
}

float Paddle::getY() const
{
    return this->getPosition().y;
}
