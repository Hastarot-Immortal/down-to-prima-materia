#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

class TextureFactory
{
private:
    std::unordered_map<std::string, sf::Texture> textures_;
public:
    TextureFactory(const fs::path& path);
    const sf::Texture& get(const std::string& key) const;
};