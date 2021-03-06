#ifndef PLAY_SCENE_HPP
#define PLAY_SCENE_HPP
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <Scene.hpp>
#include <CoreComponents.hpp>
#include <Entities/Paddle.hpp>
#include <Entities/Ball.hpp>
#include <Entities/Brick.hpp>

#include <memory>
#include <vector>
#include <string>
#include <cmath>

class PlayScene : public Scene
{
  public:
    PlayScene(const CoreComponents& components, unsigned int selectedPaddleIndex);

    void initialize() override;
    void processInput() override;
    void update() override;
    void render() const override;

  private:
    const CoreComponents& m_Components;

    std::unique_ptr<Paddle>               m_Player;
    std::unique_ptr<Ball>                 m_Ball;
    std::vector<std::unique_ptr<Brick>>   m_Bricks;
    std::vector<sf::Sprite>               m_Hearts;
    std::random_device                    m_RandomDevice;
    std::mt19937                          m_MTGenerator;
    std::uniform_real_distribution<float> m_Distributor;
    std::unique_ptr<sf::Text>             m_ScoreText;
    std::unique_ptr<sf::Text>             m_TitleText;

    short        m_Health;
    bool         m_IsPlaying;
    bool         m_IsGameOver;
    unsigned int m_Score;
};

#endif // PLAY_SCENE_HPP
