//
// Created by dominik on 21.12.25.
//

#ifndef GAME1_TRANSFORMCOMPONENT_H
#define GAME1_TRANSFORMCOMPONENT_H

#include "../Entity.h"
#include <SFML/System/Vector2.hpp>

struct TransformComponent
{
   public:
      explicit TransformComponent( const sf::Vector2f& position = sf::Vector2f( 0.f, 0.f ), float rotation = 0.f,
                                   const sf::Vector2f& scale = sf::Vector2f( 1.f, 1.f ), Entity parent = INVALID_ENTITY )
         : localPosition( position ), localRotation( rotation ), localScale( scale ), globalPosition( position ),
           globalRotation( rotation ),
           globalScale( scale ), parent( parent ), isDirty( true )
      {
      }

      [[nodiscard]] sf::Vector2f getLocalPosition() const
      {
         return localPosition;
      }

      [[nodiscard]] float getLocalRotation() const
      {
         return localRotation;
      }

      [[nodiscard]] sf::Vector2f getLocalScale() const
      {
         return localScale;
      }

      [[nodiscard]] sf::Vector2f getGlobalPosition() const
      {
         return globalPosition;
      }

      [[nodiscard]] float getGlobalRotation() const
      {
         return globalRotation;
      }

      [[nodiscard]] sf::Vector2f getGlobalScale() const
      {
         return globalScale;
      }

      [[nodiscard]] bool isTransformDirty() const
      {
         return isDirty;
      }

      // Mutators ---------------
      void move( const sf::Vector2f& offset )
      {
         localPosition += offset;
         isDirty = true;
      }

      void setPosition( const sf::Vector2f& newPosition )
      {
         localPosition = newPosition;
         isDirty = true;
      }

      void rotate( float rotation )
      {
         localRotation += rotation;
         isDirty = true;
      }

      void setRotation( float newRotation )
      {
         localRotation = newRotation;
         isDirty = true;
      }

      void scale( const sf::Vector2f& scale )
      {
         localScale.x *= scale.x;
         localScale.y *= scale.y;
         isDirty = true;
      }

      void setScale( const sf::Vector2f& newScale )
      {
         localScale = newScale;
         isDirty = true;
      }

   private:
      bool isDirty;
      // Public variables for easier access by systems. User shouldn't change this ------------

      sf::Vector2f localPosition;
      float localRotation;
      sf::Vector2f localScale;

      // Cached global transform
      sf::Vector2f globalPosition;
      float globalRotation;
      sf::Vector2f globalScale;

      // These structures form the hierarchy without having to use vectors for children, which could require heavier reallocations
      /**
       * @warning Don't change by yourself. Use transform system
       */
      Entity parent = INVALID_ENTITY;
      /**
       * @warning Don't change by yourself. Use transform system
       */
      Entity firstChild = INVALID_ENTITY;
      /**
       * @warning Don't change by yourself. Use transform system
       */
      Entity lastChild = INVALID_ENTITY;
      /**
       * @warning Don't change by yourself. Use transform system
       */
      Entity nextSibling = INVALID_ENTITY;

      unsigned int hierarchyDepth = 0;

      void setDirty()
      {
         isDirty = true;
      }

      void setUndirty()
      {
         isDirty = false;
      }

      friend class TransformSystem;
};
#endif //GAME1_TRANSFORMCOMPONENT_H
