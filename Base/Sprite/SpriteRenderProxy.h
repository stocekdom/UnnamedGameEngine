//
// Created by dominik on 22.12.25.
//

#ifndef GAME1_RENDERPROXY_H
#define GAME1_RENDERPROXY_H

#include "../Entity.h"
#include <SFML/Graphics/Sprite.hpp>

/**
 * This class acts as the data for the sprite component which only holds a soft reference to the sprite (texture path)
 * This is where the actual sprite is stored.
 * Optimizes memory access by having the actual sprites in one continuous local array inside the sprite system
 */
struct SpriteRenderProxy
{
   Entity owner = INVALID_ENTITY;
   // The value by which we sort the draw order. Currently, we use just Y.
   float sortKey = 0.0f;
   sf::Sprite sprite;
};

#endif //GAME1_RENDERPROXY_H
