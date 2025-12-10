//
// Created by dominik on 13.10.25.
//

#ifndef GAME1_COLLISIONSYSTEM_H
#define GAME1_COLLISIONSYSTEM_H

#include <vector>
#include <memory>

class Collider;

class CollisionSystem
{
   public:
      void registerCollider( const std::shared_ptr<Collider>& collider );

      [[nodiscard]] const std::vector<std::weak_ptr<Collider>>& getColliders() const;

      void update( float dt );

      void debugSwitch();

   private:
      bool isDebugged = false;
      std::vector<std::weak_ptr<Collider>> colliders;
};

#endif //GAME1_COLLISIONSYSTEM_H
