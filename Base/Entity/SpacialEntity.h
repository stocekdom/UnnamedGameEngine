//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_SPACIALENTITY_H
#define GAME1_SPACIALENTITY_H

#include "Entity.h"

class SpacialEntity : public Entity
{
   public:

      SpacialEntity( const sf::Vector2f& position, float rotation, const sf::Vector2f& scale, bool isVisible );

      // Default implementations of getters so we don't repeat code in different base classes (Actor, Collider, etc..)

      [[nodiscard]] sf::Vector2f getPosition() const override;

      [[nodiscard]] virtual sf::Vector2f getParentRelativePosition() const;

      [[nodiscard]] float getRotation() const override;

      [[nodiscard]] sf::Vector2f getScale() const override;

      [[nodiscard]] bool isVisible() const override;

      virtual void setIsVisibleEntity( bool isVisible );

      virtual void setPosition( const sf::Vector2f& newPosition );

      virtual void setRotation( float newRotation );

      virtual void setScale( const sf::Vector2f& newScale );

      virtual void move( const sf::Vector2f& offset );

      virtual void rotate( float rotation );

      virtual void scale( const sf::Vector2f& scale );

      // Overridden so entities that don't need this don't have to override every time
      void tickFixed( float fixedDt ) override;

      void tick( float deltaTime ) override;

   protected:
      bool isVisibleEntity;
      sf::Vector2f localPosition;
      float localRotation = 0;
      sf::Vector2f localScale;
};

#endif //GAME1_SPACIALENTITY_H
