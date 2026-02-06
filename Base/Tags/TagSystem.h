//
// Created by dominik on 06.02.26.
//

#ifndef GAME1_TAGSYSTEM_H
#define GAME1_TAGSYSTEM_H
#include "../ComponentSystem.h"

class TagSystem : public ComponentSystem
{
   public:
      void init( GameContext* context ) override;

      void onStart() override;

      void update( float dt ) override;

      void onBeforeComponentsDestroyed( Entity entity ) override;

      void onComponentAdded( Entity entity ) override;
};
#endif //GAME1_TAGSYSTEM_H
