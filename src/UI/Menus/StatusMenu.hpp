#include "Menu.hpp"

class StatusMenu : public Menu
{
private:
    sf::RectangleShape shape_;
    sf::Text text_;

    void drawMenu(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    StatusMenu(sf::Vector2u& windowSize, sf::Font& font);
};

StatusMenu::StatusMenu(sf::Vector2u& windowSize, sf::Font& font)
: shape_({(float)windowSize.x, windowSize.y * .1f}), 
  text_(sf::Text(font, "Player"))
{
    is_visible_ = true;
    shape_.setOutlineColor(sf::Color(23, 27, 28));
    shape_.setOutlineThickness(3.f);
    shape_.setFillColor(sf::Color(68, 72, 77));
    text_.setFillColor(sf::Color(142, 145, 137));
    text_.setPosition({10.f, 10.f});
}

void StatusMenu::drawMenu(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = getTransform();
    target.draw(shape_, states);
    target.draw(text_, states);
}