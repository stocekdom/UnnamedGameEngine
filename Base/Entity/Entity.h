//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_ENTITY_H
#define GAME1_ENTITY_H

#include <SFML/Graphics/Drawable.hpp>

class Entity
{
   public:
      // Tick with fixed time passed between frames. Usage: Simulation, physics, etc.
      virtual void tickFixed( float fixedDt ) = 0;

      // Tick with actual time passed between frames. Usage: Rendering, UI, Real time events, etc.
      virtual void tick( float deltaTime ) = 0;

      virtual bool isVisible() const = 0;

      virtual void setIsVisibleEntity( bool isVisibleEntity ) = 0;

      virtual const sf::Drawable& getDrawable() = 0;

   private:
};
#endif //GAME1_ENTITY_H
