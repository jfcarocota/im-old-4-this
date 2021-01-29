#include "HiddenBox.hh"

HiddenBox::HiddenBox(b2World*& world, float posX, float posY, float width, float height, float scale, sf::RenderWindow*& window)
{
    this->window = window;
    rigidbody = new Rigidbody(world, b2BodyType::b2_staticBody, new b2Vec2(posX, posY), (width * scale) / 2, (height * scale) / 2, 2, 1, 0);
    boxCollider = new BoxCollider(posX, posY, new sf::Color(0, 255, 0, 255), width, height, rigidbody);
    boxCollider->GetBoxShape()->setScale(scale, scale);
}

HiddenBox::~HiddenBox()
{

}

void HiddenBox::Update()
{
    boxCollider->UpdatePhysics();
    window->draw(*boxCollider->GetBoxShape());
}