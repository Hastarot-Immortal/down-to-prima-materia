#include "TextureFactory.hpp"

TextureFactory::TextureFactory(const fs::path& path)
{
    std::unordered_map<std::string, sf::Texture> textures;
    size_t parentDirLength = path.generic_string().length() + 1;

    for (const auto& entry : fs::recursive_directory_iterator(path))
    {
        auto entryPath = entry.path();
        if (entryPath.has_extension())
        {
            sf::Texture texture;
            if (texture.loadFromFile(entryPath))
            {
                auto entryPathWithoutExt = entryPath.replace_extension("");
                auto key = entryPathWithoutExt.generic_string().substr(parentDirLength);
                textures.insert({key, texture});
            }  
        }
    }
    textures_ = textures;
}

const sf::Texture& TextureFactory::get(const std::string& key) const
{
    return textures_.at(key);
}