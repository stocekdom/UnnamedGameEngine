//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_ENTITY_H
#define GAME1_ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include <vector>
#include "../TextureManager.h"
#include "../Core/Mobility.h"

class GameScene;

class CollisionSystem;

// TODO adding anything new to constructor of entities results in updating every constructor of a class inheriting from Entity. Find a better solution or use ECS.

/**
 * Base class for all entities.
 * Provides basic methods for spacial information and ticking.
 * Also creates a tree hierarchy for entities. Contains a weak pointer to the parent entity and a vector of weak pointers to children.
 * Provides default implementations for marking the entity dirty and working with parents.
 * @warning Override the implemented methods at your own risk, or call them in the overridden methods.
 */
class Entity : public std::enable_shared_from_this<Entity>
{
   public:

      virtual ~Entity() = default;

      virtual void onStart( GameScene& scene, CollisionSystem& collisionSystem ) = 0;

      // Tick with fixed time passed between frames. Usage: Simulation, physics, etc.
      virtual void tickFixed( float fixedDt ) = 0;

      // Tick with actual time passed between frames. Usage: Rendering, UI, Real time events, etc.
      virtual void tick( float deltaTime ) = 0;

      virtual std::weak_ptr<Entity> getParent();

      [[nodiscard]] virtual Mobility getMobility() const = 0;

      // Spacial information getters. Required for any entity even if it has no spacial data.
      // If an entity has no spacial data, it should return identity.
      [[nodiscard]] virtual sf::Vector2f getPosition() const = 0;

      [[nodiscard]] virtual sf::Vector2f getScale() const = 0;

      [[nodiscard]] virtual float getRotation() const = 0;

      [[nodiscard]] virtual bool isDirty() const;

      [[nodiscard]] virtual bool isVisible() const = 0;

      virtual void setDirty();

      virtual void setParent( const std::shared_ptr<Entity>& entity );

      virtual void addChild( const std::shared_ptr<Entity>& child );

      virtual const sf::Drawable& getDrawable() = 0;

   protected:
      bool isEntityDirty = false;
      std::weak_ptr<Entity> parent;
      // Container for generic children storage. Individual entities can also have the same entity stored with a specific type.
      std::vector<std::weak_ptr<Entity>> children;
};

#endif //GAME1_ENTITY_H
