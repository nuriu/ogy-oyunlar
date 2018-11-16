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
#include <Entities/Ball.hpp>

#include <memory>

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

    std::unique_ptr<Paddle> m_Player;
    std::unique_ptr<Ball>   m_Ball;
};

#endif // PLAY_SCENE_HPP
