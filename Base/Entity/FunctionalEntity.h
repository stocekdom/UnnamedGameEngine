//
// Created by dominik on 20.12.25.
//

#ifndef GAME1_FUNCTIONALENTITY_H
#define GAME1_FUNCTIONALENTITY_H

#include "../Entity.h"
#include "../GameContext.h"
#include <memory>

#define REQ_ARGS Entity id, GameContext* context
/**
 * Main entity used for game objects with custom behavior that doesn't fit into components
 * This way we can have a hybrid ECS approach, and we don't have to make many components and systems for every small functionality.
 */
class FunctionalEntity : public std::enable_shared_from_this<FunctionalEntity>
{
   public:
      FunctionalEntity() = delete;

      explicit FunctionalEntity( REQ_ARGS ) : entity( id ), context_( context )
      {
      }

      virtual ~FunctionalEntity() = default;

      virtual void onStart( GameContext* context ) = 0;

      virtual void tick( float deltaTime ) = 0;

      [[nodiscard]] Entity getEntityId() const
      {
         return entity;
      }

   protected:
      Entity entity = INVALID_ENTITY;
      GameContext* context_ = nullptr;
};
#endif //GAME1_FUNCTIONALENTITY_H
