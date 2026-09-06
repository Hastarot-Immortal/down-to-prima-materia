#pragma once
#include "Widget.hpp"
#include "TextWidget.hpp"
#include <functional>

class DynamicLabel : public TextWidget, public DynamicWidget
{
private:
    std::function<sf::String()> textUpdateFunction_;    
public:
    DynamicLabel(std::function<sf::String()> f, const sf::Font& font, sf::String text, sf::Vector2f padding)
    : TextWidget(font, text, padding), textUpdateFunction_(f) {}

    DynamicLabel(std::function<sf::String()> f, const sf::Font& font, sf::String text)
    : DynamicLabel(f, font, text, {PADDING, PADDING}) {}

    DynamicLabel(std::function<sf::String()> f, const sf::Font& font, sf::String text, float padding)
    : DynamicLabel(f, font, text, {padding, padding}) {}

    void update() override
    {
        setText(textUpdateFunction_());
    }
};

