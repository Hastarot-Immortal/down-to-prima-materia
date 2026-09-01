#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Factories/TextureFactory.hpp"

using KeyCode = sf::Keyboard::Scancode;

int main()
{
    sf::Vector2u windowSize = {1024, 768};
    sf::RenderWindow window(sf::VideoMode(windowSize), "Down to Prima Materia");

    TextureFactory textures("assets\\images");

    Player player(textures.get("player"));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                switch (key->scancode)
                {
                case KeyCode::Escape:
                    window.close();
                    break;
                case KeyCode::A:
                    player.move({-20.f, 0.f});
                    break;
                case KeyCode::W:
                    player.move({0.f, -20.f});
                    break;
                case KeyCode::S:
                    player.move({0.f, 20.f});
                    break;
                case KeyCode::D:
                    player.move({20.f, 0.f});
                    break;
                default:
                    break;
                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(player);
        window.display();
    }
}