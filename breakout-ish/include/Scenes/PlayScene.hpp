#ifndef PLAY_SCENE_HPP
#define PLAY_SCENE_HPP
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <Scene.hpp>
#include <CoreComponents.hpp>
#include <Entities/Paddle.hpp>

#include <memory>

class PlayScene : public Scene
{
  public:
    PlayScene(const CoreComponents& components, sf::Sprite paddle);

    void initialize() override;
    void processInput() override;
    void update() override;
    void render() const override;

  private:
    const CoreComponents& m_Components;

    std::unique_ptr<Paddle> m_Player;

    const float m_PaddleSpeed;
};

#endif // PLAY_SCENE_HPP
