#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Factories/TextureFactory.hpp"
#include "UI.hpp"

using KeyCode = sf::Keyboard::Scancode;

int main()
{
    sf::Vector2u windowSize = {1024, 768};
    sf::RenderWindow window(sf::VideoMode(windowSize), "Down to Prima Materia");

    TextureFactory textures("assets\\images");
    sf::Font font("assets\\fonts\\simple-pixel.otf");

    Player player(textures.get("player"));

    TextButton button(
        [&window](){ window.close(); },
        font,
        "Exit"
    );
    button.move({50.f, 50.f});

    VContainer container({
        std::make_shared<Label>(font, std::to_string(player.getHealth()) + "hp"),
        std::make_shared<Label>(font, "Hello")
    }, {100.f, std::nullopt});
    container.setOrigin({container.getSize().x / 2, container.getSize().y / 2});
    container.setPosition({windowSize.x / 2.f, windowSize.y / 2.f});

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
            else if (event->is<sf::Event::MouseMoved>()
            || event->is<sf::Event::MouseButtonPressed>())
            {
                if (const auto* mouse = event->getIf<sf::Event::MouseMoved>())
                {
                    button.handle(MouseEvent(mouse));
                } 
                else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    button.handle(MouseEvent(mouse));
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(player);
        window.draw(container);
        window.draw(button);
        window.display();
    }
}