//
// Created by dominik on 28.12.25.
//

#ifndef GAME1_OVERLAYSPRITECOMPONENT_H
#define GAME1_OVERLAYSPRITECOMPONENT_H

#include "../Entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include <string>

struct OverlaySpriteComponent
{
   explicit OverlaySpriteComponent( Entity owner, std::string texturePath )
      : owner( owner ), texturePath( std::move( texturePath ) )
   {
   }

   Entity owner;
   std::string texturePath;
   sf::Sprite sprite;
};

#endif //GAME1_OVERLAYSPRITECOMPONENT_H
