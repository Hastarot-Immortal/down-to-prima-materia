#include <SFML/Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable
{
private:
    sf::Sprite sprite_;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;    
public:
    Player(sf::Texture& texture);
    ~Player() {};

};
