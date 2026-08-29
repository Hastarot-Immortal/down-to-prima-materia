#include "Player.hpp"

Player::Player(sf::Texture& texture)
: sprite_(sf::Sprite(texture))
{}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite_, states);
}