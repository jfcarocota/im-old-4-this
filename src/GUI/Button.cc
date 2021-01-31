#include "GUI/Button.hh"

Button::Button(float posX, float posY, float width, float height, float borderSize, sf::Color* fillColor, sf::Color* borderColor, sf::RenderWindow*& window)
{
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
    this->borderSize = borderSize;
    this->fillColor = fillColor;
    this->borderColor = borderColor;
    this->window = window;
    Init();
}

Button::Button(float posX, float posY, float width, float height, float borderSize, sf::Color* fillColor, sf::Color* borderColor, 
sf::RenderWindow*& window, std::string label, const char* fontUrl, unsigned int fontSize)
{
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
    this->borderSize = borderSize;
    this->fillColor = fillColor;
    this->borderColor = borderColor;
    this->window = window;
    //this->label = label;

    font->loadFromFile(fontUrl);
    text->setFont(*font);
    text->setString(label);
    text->setCharacterSize(fontSize);
    text->setFillColor(sf::Color::Black);
    text->setPosition((posX + width / 2) - fontSize, posY);
    Init();
}

void Button::Init()
{
    rectangleShape = new sf::RectangleShape();
    rectangleShape->setPosition(*(new sf::Vector2f(posX, posY)));
    rectangleShape->setSize(*(new sf::Vector2f(width, height)));
    rectangleShape->setFillColor(*fillColor);
    rectangleShape->setOutlineColor(*borderColor);
    rectangleShape->setOutlineThickness(borderSize);
}

Button::~Button()
{
}

void Button::OnClick()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);//captura si estamos en el area de la venta de nuestor juego
    sf::Vector2f mouseTranslate = window->mapPixelToCoords(mousePos); // este captura cuanto se ha movido el mouse dentro de la ventana
    if(rectangleShape->getGlobalBounds().contains(mouseTranslate)) // si esa traslación fue sobre la forma de nuestro rectangulo
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            std::cout << "click" << std::endl;
        }
    }
}

void Button::Update()
{
    OnClick();
    window->draw(*rectangleShape);
    window->draw(*text);
}