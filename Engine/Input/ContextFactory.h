//
// Created by dominik on 28.11.25.
//

#ifndef GAME1_CONTEXTFACTORY_H
#define GAME1_CONTEXTFACTORY_H

#include "InputContext.h"
#include <memory>

class ContextFactory
{
   public:
      static std::shared_ptr<InputContext> createGameContext();

      static std::shared_ptr<InputContext> createPauseContext();

      static std::shared_ptr<InputContext> createBuildingPlacingContext();

      static std::shared_ptr<InputContext> createUIControllerContext();
};
#endif //GAME1_CONTEXTFACTORY_H
