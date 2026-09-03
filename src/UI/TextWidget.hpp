#pragma once
#include "BackgroundWidget.hpp"
#include <SFML/Graphics/Text.hpp>

class TextWidget : public BackgroundWidget
{
protected:
    sf::Text text_;

    static void fitTextInsidePadding(sf::Text& text, sf::FloatRect bounds, sf::Vector2f padding)
    {
        sf::Vector2f sizeWithoutPadding = {
            std::max(0.f, bounds.size.x - padding.x * 2.f), 
            std::max(0.f, bounds.size.y - padding.y * 2.f)
        };
        sf::FloatRect textBounds = text.getLocalBounds();

        float scaleX = sizeWithoutPadding.x / textBounds.size.x;
        float scaleY = sizeWithoutPadding.y / textBounds.size.y;
        float finalScale = std::min(scaleX, scaleY);
            
        text.setScale({finalScale, finalScale});
        text.setPosition({
            bounds.position.x + padding.x - (textBounds.position.x * finalScale), 
            bounds.position.y + padding.y - (textBounds.position.y * finalScale)
        });
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(shape_, states);
        target.draw(text_, states);
    }
public:
    TextWidget(const sf::Font& font, sf::String text, sf::Vector2f padding)
    : BackgroundWidget(padding), text_(sf::Text(font, text))
    {
        shape_.setSize({
            text_.getLocalBounds().size.x + padding_.x * 2.f,
            text_.getLocalBounds().size.y + padding_.y * 2.f
        });
        text_.setFillColor(TEXT_COLOR);

        fitTextInsidePadding(text_, shape_.getLocalBounds(), padding_);
    }

    TextWidget(const sf::Font&& font, sf::String text, sf::Vector2f padding) = delete;

        const sf::String& getText() const { return text_.getString(); }
    void setText(const sf::String& text) { text_.setString(text); }

    const unsigned int getCharacterSize() const { return text_.getCharacterSize(); }
    
    void setCharacterSize(unsigned int size)
    {
        text_.setCharacterSize(size);
        auto textBounds = text_.getLocalBounds();
        shape_.setSize({
            textBounds.size.x + padding_.x * 2.f,
            textBounds.size.y + padding_.y * 2.f,
        });
    }

    const std::uint32_t getStyle() const { return text_.getStyle(); }
    void setStyle(std::uint32_t style) { text_.setStyle(style); }

    const sf::Color getTextColor() const { return text_.getFillColor(); }
    void setTextColor(sf::Color color) { text_.setFillColor(color); }

    void setSize(sf::Vector2f size) override
    {
        shape_.setSize(size);
        fitTextInsidePadding(text_, shape_.getLocalBounds(), padding_);
    }
};
