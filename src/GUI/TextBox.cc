#include "GUI/TextBox.hh"

TextBox::TextBox(float posX, float posY, float width, float height, float borderSize, 
sf::RenderWindow*& window, std::string label, const char* fontUrl, unsigned int fontSize)
{
    
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
    this->borderSize = borderSize;
    this->fillColor = new sf::Color(0, 0, 0, 180);
    this->borderColor = new sf::Color(0, 0, 0, 255);
    this->window = window;
    //this->label = label;

    font->loadFromFile(fontUrl);
    text->setFont(*font);
    text->setString(label);
    text->setCharacterSize(fontSize);
    text->setFillColor(sf::Color::White);
    text->setPosition(posX + 5, posY + 5);

    rectangleShape = new sf::RectangleShape();
    rectangleShape->setPosition(*(new sf::Vector2f(posX, posY)));
    rectangleShape->setSize(*(new sf::Vector2f(width + std::abs(width - text->getLocalBounds().width) + 10, height)));
    rectangleShape->setFillColor(*fillColor);
    rectangleShape->setOutlineColor(*borderColor);
    rectangleShape->setOutlineThickness(borderSize);
}

TextBox::~TextBox()
{

}

void TextBox::Update()
{
    window->draw(*rectangleShape);
    window->draw(*text);
}