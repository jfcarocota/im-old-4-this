#pragma once

#include<SFML/Graphics.hpp>
#include <iostream>

class TextBox
{
private:
    sf::RectangleShape* rectangleShape;
    float posX, posY, width, height, borderSize;
    sf::Color* fillColor;
    sf::Color* borderColor;
    sf::RenderWindow* window;
    sf::Font* font{new sf::Font()};
    sf::Text* text{new sf::Text()};
    float alive{};
    float currentTime{};
public:
    TextBox(float posX, float posY, float width, float height, float borderSize, 
    sf::RenderWindow*& window, const char* fontUrl, unsigned int fontSize, float alive);
    ~TextBox();
    void Update(float deltaTime);
    void Show(std::string label);
};
