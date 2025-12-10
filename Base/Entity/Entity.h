//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_ENTITY_H
#define GAME1_ENTITY_H

#include "../Core/Mobility.h"
#include "../GameContext.h"
#include "../Core/UUID.h"
#include "../Core/SpawnCategory.h"
#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include <vector>

/**
 * Base class for all entities.
 * Provides basic methods for spacial information and ticking.
 * Also creates a tree hierarchy for entities. Contains a weak pointer to the parent entity and a vector of weak pointers to children.
 * Provides default implementations for marking the entity dirty and working with parents.
 * @warning Override the implemented methods at your own risk or call them in the overridden methods.
 */
class Entity : public std::enable_shared_from_this<Entity>
{
   public:
      virtual ~Entity() = default;

      // TODO passing the context should be fixed with ECS
      virtual void onStart( GameContext* context ) = 0;

      // Tick with fixed time passed between frames. Usage: Simulation, physics, etc.
      virtual void tickFixed( float fixedDt ) = 0;

      // Tick with actual time passed between frames. Usage: Rendering, UI, Real time events, etc.
      virtual void tick( float deltaTime ) = 0;

      std::weak_ptr<Entity> getParent();

      [[nodiscard]] virtual Mobility getMobility() const = 0;

      [[nodiscard]] virtual SpawnCategory getSpawnCategory() const = 0;

      // TODO these setters aren't good and should only be called internally by scene. Should be fixed with ECS
      virtual void setSpawnCategory( SpawnCategory newSpawnCategory ) = 0;

      virtual void setMobility( Mobility newMobility ) = 0;

      // Spacial information getters. Required for any entity even if it has no spacial data.
      // If an entity has no spacial data, it should return identity.
      [[nodiscard]] virtual sf::Vector2f getPosition() const = 0;

      [[nodiscard]] virtual sf::Vector2f getScale() const = 0;

      [[nodiscard]] virtual float getRotation() const = 0;

      [[nodiscard]] bool isDirty() const;

      [[nodiscard]] virtual bool isVisible() const = 0;

      [[nodiscard]] UUID getId() const;

      void setDirty();

      void setParent( const std::shared_ptr<Entity>& entity );

      void addChild( const std::shared_ptr<Entity>& child );

      virtual const sf::Drawable& getDrawable() = 0;

   protected:
      UUID id;
      bool isEntityDirty = false;
      std::weak_ptr<Entity> parent;
      // Container for generic children storage. Individual entities can also have the same entity stored with a specific type.
      std::vector<std::weak_ptr<Entity>> children;
};

#endif //GAME1_ENTITY_H
