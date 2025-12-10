//
// Created by dominik on 14.11.25.
//
#include "ResourceManager.h"
#include "Logging/Logger.h"

const sf::Texture& ResourceManager::loadTexture( const std::string& path )
{
   auto texture = textures.find( path );

   if( texture == textures.end() )
   {
      auto newTexture = std::make_unique<sf::Texture>();

      if( !newTexture->loadFromFile( path ) )
      {
         LOG_ERROR( "Could not load texture at " + path );
      }

      textures[ path ] = std::move( newTexture );
   }

   return *textures.at( path );
}

const sf::Font& ResourceManager::loadFont( const std::string& path )
{
   auto font = fonts.find( path );

   if( font == fonts.end() )
   {
      auto newFont = std::make_unique<sf::Font>();

      if( !newFont->loadFromFile( path ) )
      {
         LOG_ERROR( "Could not load font at " + path );
      }

      fonts[ path ] = std::move( newFont );
   }

   return *fonts.at( path );
}
