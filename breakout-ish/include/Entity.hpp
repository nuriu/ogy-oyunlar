#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once

class Entity
{
  public:
    virtual void initialize()   = 0;
    virtual void processInput() = 0;
    virtual void update()       = 0;
    virtual void render() const = 0;

    virtual ~Entity() = default;
};

#endif // ENTITY_HPP
