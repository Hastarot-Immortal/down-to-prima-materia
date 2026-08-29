#pragma once

#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable, protected sf::Transformable
{
protected:
    bool is_visible_;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        if (is_visible_) drawMenu(target, states);
    }
public:
    void switchVisible() { is_visible_ = !is_visible_; }

    virtual void drawMenu(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};