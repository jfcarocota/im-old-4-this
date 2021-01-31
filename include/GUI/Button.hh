#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

class Button
{
    private:
        sf::RectangleShape* rectangleShape;
        float posX, posY, width, height, borderSize;
        sf::Color* fillColor;
        sf::Color* borderColor;
        sf::RenderWindow* window;
        sf::Font* font{new sf::Font()};
        sf::Text* text{new sf::Text()};
        //std::string label{};
    public:
        void Init();
        void Update();
        bool OnClick();
        Button(float, float, float, float, float, sf::Color*, sf::Color*, sf::RenderWindow*&);
        Button(float, float, float, float, float, sf::Color*, sf::Color*, sf::RenderWindow*&, std::string, const char*, unsigned int);
        ~Button();
};
