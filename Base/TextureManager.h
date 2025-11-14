//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_TEXTUREMANAGER_H
#define GAME1_TEXTUREMANAGER_H

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

class TextureManager
{
   public:
      const sf::Texture& loadTexture( const std::string& path );

   private:
      std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
};
#endif //GAME1_TEXTUREMANAGER_H
