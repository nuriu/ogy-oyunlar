#ifndef PADDLE_SELECT_SCENE_HPP
#define PADDLE_SELECT_SCENE_HPP
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include <Scene.hpp>
#include <CoreComponents.hpp>
#include <Scenes/PlayScene.hpp>

#include <memory>
#include <vector>

class PaddleSelectScene : public Scene
{
  public:
    explicit PaddleSelectScene(const CoreComponents& components);

    void initialize() override;
    void processInput() override;
    void update() override;
    void render() const override;

  private:
    const CoreComponents& m_Components;

    std::unique_ptr<sf::Text> m_Title;
    std::unique_ptr<sf::Text> m_LeftArrow;
    std::unique_ptr<sf::Text> m_RightArrow;
    std::vector<sf::Sprite>   m_Paddles;

    unsigned int m_SelectedPaddleIndex;
};

#endif // PADDLE_SELECT_SCENE_HPP
