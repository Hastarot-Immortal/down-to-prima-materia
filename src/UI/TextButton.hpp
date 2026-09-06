#pragma once
#include "Widget.hpp"
#include <functional>
#include <utility>
#include <type_traits>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class TextButton : public InteractableWidget, public TextWidget
{    
private:
    std::function<void()> onPressed_;
    sf::Color defaultColor_ = BACKGROUND_COLOR;
    sf::Color hoverColor_ = HOVER_COLOR;
public:
    TextButton(std::function<void()> onPressed, const sf::Font& font, sf::String text, sf::Vector2f padding)
    : TextWidget(font, text, padding), onPressed_(onPressed) {}

    TextButton(std::function<void()> onPressed, const sf::Font&& font, sf::String text, sf::Vector2f padding) = delete;

    TextButton(std::function<void()> onPressed, const sf::Font& font, sf::String text)
    : TextButton(onPressed, font, text, {PADDING, PADDING}) {}

    TextButton(std::function<void()> onPressed, const sf::Font& font, sf::String text, float padding)
    : TextButton(onPressed, font, text, {padding, padding}) {}

    void onPressed() override { onPressed_(); }

    void onHoverStateChanged() override
    {
        if (isHovered_) 
            setBackgroundColor(hoverColor_);            
        else 
            setBackgroundColor(defaultColor_);
    }
};