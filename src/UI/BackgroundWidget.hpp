#pragma once
#include "Widget.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class BackgroundWidget : virtual public Widget
{
protected:
    sf::Vector2f padding_;    
    sf::RectangleShape shape_;

    static void setDefaultSettings(sf::RectangleShape& shape)
    {
        shape.setFillColor(BACKGROUND_COLOR);
        shape.setOutlineColor(OUTLINE_COLOR);
        shape.setOutlineThickness(2.f);
    }
public:
    BackgroundWidget(sf::Vector2f padding)
    : padding_(padding), shape_(sf::RectangleShape({0.f, 0.f})) 
    {
        setDefaultSettings(shape_);
    }

    const sf::Color getBackgroundColor() const { return shape_.getFillColor(); }
    void setBackgroundColor(sf::Color color) { shape_.setFillColor(color); }

    const sf::Color getOutlineColor() const { return shape_.getOutlineColor(); }
    void setOutlineColor(sf::Color color) { shape_.setOutlineColor(color); }

    const float getOutlineThickness() const { return shape_.getOutlineThickness(); }
    void getOutlineThickness(float thickness) { shape_.setOutlineThickness(thickness); }

    const sf::FloatRect getBounds() const override 
    { 
        return getTransform().transformRect(shape_.getLocalBounds()); 
    }
    const sf::Vector2f getSize() const override { return shape_.getSize(); }
};
