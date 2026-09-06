#pragma once
#include "Widget.hpp"
#include "BackgroundWidget.hpp"
#include <functional>
#include <utility>
#include <type_traits>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class ImageButton : public InteractableWidget, public BackgroundWidget
{
private:
    std::function<void()> onPressed_;
    sf::Sprite image_;
    sf::Color defaultColor_ = BACKGROUND_COLOR;
    sf::Color hoverColor_ = HOVER_COLOR;

    static void fitSpriteInsidePadding(sf::Sprite& sprite, sf::FloatRect bounds, sf::Vector2f padding)
    {
        sf::Vector2f sizeWithoutPadding = {
            std::max(0.f, bounds.size.x - padding.x * 2.f), 
            std::max(0.f, bounds.size.y - padding.y * 2.f)
        };
        
        sf::FloatRect spriteBounds = sprite.getLocalBounds();
        float scaleX = sizeWithoutPadding.x / spriteBounds.size.x;
        float scaleY = sizeWithoutPadding.y / spriteBounds.size.y;
        float finalScale = std::min(scaleX, scaleY);
        
        sprite.setScale({finalScale, finalScale});

        sf::Vector2f scaledSize = {
            spriteBounds.size.x * finalScale,
            spriteBounds.size.y * finalScale
        };
        
        sprite.setPosition({
            bounds.position.x + (bounds.size.x - scaledSize.x) / 2.f - (spriteBounds.position.x * finalScale),
            bounds.position.y + (bounds.size.y - scaledSize.y) / 2.f - (spriteBounds.position.y * finalScale)
        });
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(shape_, states);
        target.draw(image_, states);
    }
public:
    ImageButton(std::function<void()> onPressed, const sf::Texture& texture, sf::Vector2f padding)
    : BackgroundWidget(padding), onPressed_(onPressed), image_(texture)
    {
        shape_.setSize({
            image_.getLocalBounds().size.x + padding_.x * 2.f,
            image_.getLocalBounds().size.y + padding_.y * 2.f
        });

        fitSpriteInsidePadding(image_, shape_.getLocalBounds(), padding_);
    }

    ImageButton(std::function<void()> onPressed, const sf::Texture& texture, float padding)
    : ImageButton(onPressed, texture, {padding, padding}) {}

    ImageButton(std::function<void()> onPressed, const sf::Texture& texture)
    : ImageButton(onPressed, texture, {PADDING, PADDING}) {}

    ImageButton(const sf::Texture&& font, sf::Vector2f padding) = delete;

    void setSize(sf::Vector2f size) override
    {
        shape_.setSize(size);
        fitSpriteInsidePadding(image_, shape_.getLocalBounds(), padding_);
    }

    void onPressed() override { onPressed_(); }

    void onHoverStateChanged() override
    {
        if (isHovered_) 
            setBackgroundColor(hoverColor_);
        else 
            setBackgroundColor(defaultColor_);
    }
};
