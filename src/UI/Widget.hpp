#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

inline constexpr sf::Color BACKGROUND_COLOR = sf::Color(46, 52, 64, 150);
inline constexpr sf::Color TEXT_COLOR = sf::Color::White;
inline constexpr sf::Color OUTLINE_COLOR = sf::Color::Black;

class Widget : public sf::Drawable, public sf::Transformable
{
public:
    virtual sf::FloatRect getBounds() const = 0;
    virtual const sf::Vector2f getSize() const = 0;
    virtual void setSize(sf::Vector2f size) = 0;
};
