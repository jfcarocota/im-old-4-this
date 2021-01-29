#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Rigidbody.hh"
#include "BoxCollider.hh"

class HiddenBox
{
private:
        Rigidbody* rigidbody{};
        BoxCollider* boxCollider{};
        sf::RenderWindow* window;
public:
    HiddenBox(b2World*& world, float posX, float posY, float width, float height, float scale, sf::RenderWindow*& window);
    ~HiddenBox();

    void Update();
};
