#pragma once
#include "Widget.hpp"
#include <functional>
#include <utility>
#include <type_traits>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

class TextButton : public InteractableWidget, public TextWidget
{    
private:
    std::function<void()> f_;
    sf::Color defaultColor_ = BACKGROUND_COLOR;
    sf::Color hoverColor_ = HOVER_COLOR;
public:
    TextButton(std::function<void()> f, const sf::Font& font, sf::String text, sf::Vector2f padding)
    : f_(f), TextWidget(font, text, padding) {}
    
    TextButton(std::function<void()> f, const sf::Font&& font, sf::String text, sf::Vector2f padding) = delete;

    TextButton(std::function<void()> f, const sf::Font& font, sf::String text)
    : TextButton(f, font, text, {PADDING, PADDING}) {}

    TextButton(std::function<void()> f, const sf::Font& font, sf::String text, float padding)
    : TextButton(f, font, text, {padding, padding}) {}

    void onPressed() override { f_(); }

    void onHoverStateChanged() override
    {
        if (isHovered_)
            setBackgroundColor(hoverColor_);
        else
            setBackgroundColor(defaultColor_);
    }
};