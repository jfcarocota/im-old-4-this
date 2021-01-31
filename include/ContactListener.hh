#pragma once
#include<box2d/box2d.h>
#include<SFML/Graphics.hpp>
#include<iostream>
#include "Score.hh"
#include "GameObject.hh"
#include "SFX.hh"
#include "GUI/TextBox.hh"

class ContactListener : public b2ContactListener
{
    private:
        Score* score;
        std::vector<GameObject*>* items;
        int sceneIndex{};
        SFX* sfx;
        TextBox* textBox{};
    public:
        ContactListener(Score*&, std::vector<GameObject*>*&, TextBox*& textBox);
        ~ContactListener();
        
        void BeginContact(b2Contact*);
        void EndContact(b2Contact*);
        int GetSceneIndex() const;
};
