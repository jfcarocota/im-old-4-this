#pragma once

#include<SFML/Graphics.hpp>
#include<box2d/box2d.h>
#include "BoxCollider.hh"

class GameObject
{
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;
        float cropPosX;  
        float cropPosY;
        float cropWidth;
        float cropHeight;
        float scaleX;
        float scaleY;
        BoxCollider* boxCollider;
        float tileBaseWidth;
        float tileBaseHeight;
        sf::RenderWindow* window;

        const char* tagName{"default"};

        bool debug{};

        void InitSprite(b2World*&, b2Vec2*, b2BodyType);
    public:
        GameObject(sf::Texture*& texture, float cropPosX, float cropPosY, float cropWidth, 
        float cropHeight, float scaleX, float scaleY, b2Vec2* position, b2BodyType bodyType,b2World*& world, sf::RenderWindow*& window);
        ~GameObject();
        sf::Sprite* GetSprite();
         BoxCollider* GetCollider() const;
        void Update();
        void SetPosition(float, float);
        const char* GetTagName() const;
        void SetTagName(const char*);
        void SetDebug(bool);
        bool GetDebug() const;
};