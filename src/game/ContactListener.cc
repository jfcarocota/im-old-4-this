#include "ContactListener.hh"
#include "GameObject.hh"
#include "Tile.hh"
#include<iostream>
#include<cstring>
#include<algorithm>

ContactListener::ContactListener(Score*& score, std::vector<GameObject*>*& items, std::vector<GameObject*>*& go4Delete,TextBox*& textBox)
{
    sfx = new SFX();
    this->score = score;
    this->items = items;
    this->go4Delete = go4Delete;
    this->textBox = textBox;
}

ContactListener::~ContactListener()
{
}

int ContactListener::GetSceneIndex() const
{
    return sceneIndex;
}

void ContactListener::BeginContact(b2Contact* contact)
{
    GameObject* bodyDataA = (GameObject*) contact->GetFixtureA()->GetBody()->GetUserData();
    GameObject* bodyDataB = (GameObject*) contact->GetFixtureB()->GetBody()->GetUserData();

    if(bodyDataA && bodyDataB)
    {
        if(std::strcmp(bodyDataA->GetTagName(), "player") == 0 && std::strcmp(bodyDataB->GetTagName(), "item") == 0)
        {
            //std::cout << "collected" << std::endl;
            //score->AddPoints(5);
            items->erase(std::remove(items->begin(), items->end(), bodyDataB), items->end());
            bodyDataB->~GameObject();
            sfx->PlaySFX(0);
        }
        if(std::strcmp(bodyDataA->GetTagName(), "player") == 0 && std::strcmp(bodyDataB->GetTagName(), "keyChest") == 0)
        {
            //items->erase(std::remove(items->begin(), items->end(), bodyDataB), items->end());
            //bodyDataB->~GameObject();
            go4Delete->push_back(bodyDataB);
            sfx->PlaySFX(0);
        }
        /*if(std::strcmp(bodyDataA->GetTagName(), "player") == 0 && std::strcmp(bodyDataB->GetTagName(), "stairs") == 0)
        {
            std::cout << "stairs" << std::endl;
            bodyDataB->~GameObject();
            sceneIndex++;
        }*/

        if(std::strcmp(bodyDataA->GetTagName(), "player") == 0 && std::strcmp(bodyDataB->GetTagName(), "chair") == 0)
        {
            std::cout << "chair" << std::endl;
            textBox->Show("You have decided to sit in the chair");
        }

        if(std::strcmp(bodyDataA->GetTagName(), "player") == 0 && std::strcmp(bodyDataB->GetTagName(), "pc") == 0)
        {
            std::cout << "chair" << std::endl;
            textBox->Show("This brings me good memories");
        }
    }
}

void ContactListener::EndContact(b2Contact* contact)
{

}