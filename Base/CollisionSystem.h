//
// Created by dominik on 13.10.25.
//

#ifndef GAME1_COLLISIONSYSTEM_H
#define GAME1_COLLISIONSYSTEM_H

#include <vector>
#include <memory>
#include "ICollider.h"

class CollisionSystem
{
   public:
      void registerCollider( const std::shared_ptr<ICollider>& collider );

      [[nodiscard]] const std::vector<std::weak_ptr<ICollider>>& getColliders() const;

      void update( float dt );

      static bool pointRectangleCollisionHelper( const ColliderPoint* point, const ColliderRect* rect, CollisionInfo& info );

   private:
      std::vector<std::weak_ptr<ICollider>> colliders;
};

#endif //GAME1_COLLISIONSYSTEM_H
