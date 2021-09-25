#include "HiddenBox.hh"

HiddenBox::HiddenBox(b2World*& world, float posX, float posY, float width, float height, float scale, sf::RenderWindow*& window)
{
    this->window = window;
    rigidbody = new Rigidbody(world, b2BodyType::b2_staticBody, new b2Vec2(posX, posY), (width * scale) / 2, (height * scale) / 2, 2, 1, 0,  new b2Vec2(0.f, 0.f), 0.f);
    boxCollider = new BoxCollider(posX, posY, new sf::Color(0, 255, 0, 255), width, height, rigidbody);
    boxCollider->GetBoxShape()->setScale(scale, scale);
}

HiddenBox::~HiddenBox()
{

}

void HiddenBox::Update()
{
    boxCollider->UpdatePhysics();
    if(debug)
    {
        window->draw(*boxCollider->GetBoxShape());
    }
}

void HiddenBox::SetDebugMode(bool debug)
{
    this->debug = debug;
}
