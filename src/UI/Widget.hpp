#pragma once
#include "../Utility/BoolSet.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

inline constexpr sf::Color BACKGROUND_COLOR = sf::Color(46, 52, 64, 150);
inline constexpr sf::Color HOVER_COLOR = sf::Color(81, 92, 115, 255);
inline constexpr sf::Color TEXT_COLOR = sf::Color::White;
inline constexpr sf::Color OUTLINE_COLOR = sf::Color::Black;
inline constexpr float PADDING = 10.f;
inline constexpr float OUTLINE_THICKNESS = 2.f;

inline constexpr int VISIBILITY = 0;
inline constexpr int HOVER = 1;

class Widget : public sf::Drawable, public sf::Transformable
{
protected:
    BoolSet states_ = 1;
public:
    virtual const sf::FloatRect getBounds() const = 0;
    virtual const sf::Vector2f getSize() const = 0;
    virtual void setSize(sf::Vector2f size) = 0;

    bool isVisible() const { return states_[VISIBILITY]; }

    void setVisibility(bool visibility) { visibility ? states_.setTrue(VISIBILITY) : states_.setFalse(VISIBILITY); }

    void switchVisibility() { states_.flip(VISIBILITY); }

    bool isIntersected(sf::Vector2i mousePosition)
    {
        return getBounds().contains({(float)mousePosition.x, (float)mousePosition.y});
    }
};

class MouseEvent
{
public:
    sf::Vector2i position_;
    std::optional<sf::Mouse::Button> button_;

    MouseEvent(const sf::Event::MouseMoved* event)
    : position_(event->position), button_(std::nullopt) {}

    MouseEvent(const sf::Event::MouseButtonPressed* event)
    : position_(event->position), button_(event->button) {}
};

class InteractableWidget : virtual public Widget
{
public:
    virtual void onHoverStateChanged() {}

    virtual void onPressed() = 0;

    bool isHovered() const { return states_[HOVER]; }

    virtual void handle(MouseEvent& event)
    {
        if (isVisible() && isIntersected(event.position_))
        {
            states_.setTrue(HOVER);
            if (event.button_.has_value() && event.button_ == sf::Mouse::Button::Left) 
                onPressed();
        } 
        else 
            states_.setFalse(HOVER);
        onHoverStateChanged();
    }
};

class DynamicWidget : virtual public Widget
{
public:
    virtual void update() = 0;
};