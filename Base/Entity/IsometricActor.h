//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_ISOMETRICACTOR_H
#define GAME1_ISOMETRICACTOR_H

#include "Actor.h"

/**
 * Base class for actors that are drawn in isometric projection
 * Inherits all functionality from Actor including spacial information and sprite handling
 * In addition adds height information for isometric projection to mimic 3D effect
 */
class IsometricActor : public Actor
{
   public:
      explicit IsometricActor( SpawnCategory spawnCategory, Mobility mobilityStatus, sf::Vector2f position = { 0, 0 },
                               float rotation = 0, sf::Vector2f scale = { 1, 1 }, float height = 0, bool isVisible = true );

      float getHeight() const;

      void setHeight( float newHeight );

      void tick( float deltaTime ) override;

      sf::Vector2f getPosition() const override;

   private:
      float localHeight;
};

#endif //GAME1_ISOMETRICACTOR_H
