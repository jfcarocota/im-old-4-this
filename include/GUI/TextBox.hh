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
public:
    TextBox(float posX, float posY, float width, float height, float borderSize, 
    sf::RenderWindow*& window, std::string label, const char* fontUrl, unsigned int fontSize);
    ~TextBox();
    void Update();
};
