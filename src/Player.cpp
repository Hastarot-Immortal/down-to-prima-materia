#include "Player.hpp"

Player::Player(const sf::Texture& texture)
: sprite_(sf::Sprite(texture)), health_(100)
{}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite_, states);
}