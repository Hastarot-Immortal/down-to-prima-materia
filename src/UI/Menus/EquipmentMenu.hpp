#include "Menu.hpp"

class EquipmentMenu : public Menu
{
private:
    sf::RectangleShape shape_;
public:
    EquipmentMenu(sf::Vector2u& windowSize);

    void drawMenu(sf::RenderTarget& target, sf::RenderStates states) const override;
};

EquipmentMenu::EquipmentMenu(sf::Vector2u& windowSize)
: shape_({windowSize.x * .8f, windowSize.y * .8f})
{
    auto size = shape_.getSize();
    shape_.setOrigin({size.x / 2, size.y / 2});
    shape_.setPosition({windowSize.x * .5f, windowSize.y * .5f});
    shape_.setOutlineColor(sf::Color(23, 27, 28));
    shape_.setOutlineThickness(3.f);
    shape_.setFillColor(sf::Color(105, 110, 112));
}

void EquipmentMenu::drawMenu(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = getTransform();
    target.draw(shape_, states);
}