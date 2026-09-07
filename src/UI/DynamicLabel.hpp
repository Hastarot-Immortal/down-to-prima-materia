#pragma once
#include "Widget.hpp"
#include "TextWidget.hpp"
#include <functional>

class DynamicLabel : public TextWidget, public DynamicWidget
{
private:
    std::function<sf::String()> textUpdateFunction_;    
public:
    DynamicLabel(std::function<sf::String()> f, const sf::Font& font, sf::Vector2f padding)
    : TextWidget(font, f(), padding), textUpdateFunction_(f) {}

    DynamicLabel(std::function<sf::String()> f, const sf::Font& font)
    : DynamicLabel(f, font, {PADDING, PADDING}) {}

    DynamicLabel(std::function<sf::String()> f, const sf::Font& font, float padding)
    : DynamicLabel(f, font, {padding, padding}) {}

    void update() override
    {
        if (!isVisible()) return;
        setText(textUpdateFunction_());
    }
};