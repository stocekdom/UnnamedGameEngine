//
// Created by dominik on 14.11.25.
//
#include "TextureManager.h"

const sf::Texture& TextureManager::loadTexture( const std::string& path )
{
   auto texture = textures.find( path );

   if( texture == textures.end() )
   {
      auto newTexture = std::make_unique<sf::Texture>();

      if( !newTexture->loadFromFile( path ) )
      {
         throw std::runtime_error( "Could not load texture at " + path );
      }

      textures[ path ] = std::move( newTexture );
   }

   return *textures.at( path );
}

