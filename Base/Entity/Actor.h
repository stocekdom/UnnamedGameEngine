//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_ACTOR_H
#define GAME1_ACTOR_H
#include <SFML/System/Vector2.hpp>

#include "FunctionalEntity.h"

struct ActorParams
{
   sf::Vector2f position = { 0.f, 0.f };
   float rotation = 0.f;
   sf::Vector2f scale = { 1.f, 1.f };
};

/**
 * Base class for all entities that can be drawn on the screen
 * Uses basic SFML sprite for drawing. Can be instantiated but doesn't have a texture for the sprite.
 * Provides all functionality for spacial information, ticking, and sprite handling.
 * Provides necessary functionality for handling the sprite, spacial information, entity hierarchy, and ticking
 * @warning Override the implemented methods at your own risk or call them in the overridden methods.
 */
class Actor : public FunctionalEntity
{
   public:
      Actor( REQ_ARGS, const ActorParams& params = ActorParams() );

      void onStart( GameContext* context ) override;

      void tick( float deltaTime ) override;
};

#endif //GAME1_ACTOR_H
