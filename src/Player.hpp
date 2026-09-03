#include <SFML/Graphics.hpp>
#include <cstdint>
#include <algorithm>

class Player : public sf::Drawable, public sf::Transformable
{
private:
    sf::Sprite sprite_;
    std::uint8_t health_;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;    
public:
    Player(const sf::Texture& texture);
    ~Player() {};

    const std::uint8_t getHealth() const { return health_; }
    
    void setHealth(int health) 
    { 
        health_ = std::clamp(health, 0, 100); 
    }
};
