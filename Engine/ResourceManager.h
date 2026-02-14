//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_RESOURCEMANAGER_H
#define GAME1_RESOURCEMANAGER_H

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <SFML/Graphics/Font.hpp>

class ResourceManager
{
   public:
      const sf::Texture& loadTexture( const std::string& path );

      const sf::Font& loadFont( const std::string& path );

   private:
      std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
      std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
};
#endif //GAME1_RESOURCEMANAGER_H
