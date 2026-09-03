#pragma once
#include "TextWidget.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Label : public TextWidget
{
public:
    Label(const sf::Font& font, sf::String text, sf::Vector2f padding)
    : TextWidget(font, text, padding) {}

    Label(const sf::Font& font, sf::String text)
    : Label(font, text, {PADDING, PADDING}) {}

    Label(const sf::Font& font, sf::String text, float padding)
    : Label(font, text, {padding, padding}) {}
};