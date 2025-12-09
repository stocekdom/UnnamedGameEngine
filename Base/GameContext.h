//
// Created by dominik on 01.11.25.
//

#ifndef GAME1_GAMECONTEXT_H
#define GAME1_GAMECONTEXT_H

#include <memory>
#include "Scene.h"
#include "Collision/CollisionSystem.h"
#include "ResourceManager.h"
#include "Input/InputSystem.h"
#include "Event/EventSystem.h"
#include "UI/UISystem.h"
#include "GameMap/GameMapSystem.h"
#include "Data/ItemRegistry.h"
#include "Time/TimeManager.h"

/**
 * Simple context for global systems.
 * @warning Do not use with non-global systems.
 */
struct GameContext {
   std::shared_ptr<GameScene> scene;
   std::shared_ptr<CollisionSystem> collisionSystem;
   std::shared_ptr<ResourceManager> resourceManager;
   std::shared_ptr<InputSystem> inputSystem;
   std::shared_ptr<EventSystem> eventSystem;
   std::shared_ptr<GameMapSystem> gameMapSystem;
   std::shared_ptr<UISystem> uiSystem;
   std::shared_ptr<ItemRegistry> itemRegistry;
   std::shared_ptr<TimeManager> timeManager;
};

#endif //GAME1_GAMECONTEXT_H
