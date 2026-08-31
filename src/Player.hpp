#include <SFML/Graphics.hpp>
#include <cstdint>

class Player : public sf::Drawable, public sf::Transformable
{
private:
    sf::Sprite sprite_;
    std::uint8_t health_;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;    
public:
    Player(const sf::Texture& texture);
    ~Player() {};

    std::uint8_t getHealth() { return health_; }
};
