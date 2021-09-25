#include "Character.hh"

Character::Character(sf::Texture*& texture, float cropPosX, float cropPosY, float cropWidth, 
float cropHeight, float scaleX, float scaleY, b2Vec2* position, b2BodyType bodyType, b2World*& world, sf::RenderWindow*& window) : 
GameObject(texture, cropPosX, cropPosY, cropWidth, cropHeight, scaleX, scaleY, position, bodyType, world, window)
{
    sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);
    boxCollider->GetBoxShape()->setOrigin(sprite->getOrigin());
    boxCollider->FreezeRotation();
}

void Character::Move(b2Vec2* direction)
{
    boxCollider->Move(direction);
}

void Character::FlipSpriteX(float x)
{
    sprite->setScale( x > 0 ? scaleX : x < 0 ? -scaleX : sprite->getScale().x, scaleY);
}

void Character::SetAnimations(Animation** animations)
{
    this->animations = animations;
}

Animation* Character::GetAnimation(int index) const
{
    return *(animations + index);
}

Character::~Character(){}