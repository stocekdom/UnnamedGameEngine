//
// Created by dominik on 01.11.25.
//

#ifndef GAME1_GAMECONTEXT_H
#define GAME1_GAMECONTEXT_H

#include <memory>
#include "Scene.h"
#include "ResourceManager.h"
#include "Input/InputSystem.h"
#include "Event/EventSystem.h"
#include "UI/UISystem.h"
#include "GameMap/GameMapSystem.h"
#include "Data/ItemRegistry.h"
#include "Data/PlayerInventoryComponent.h"
#include "Sprite/SpriteSystem.h"
#include "Time/TimeManager.h"
#include "Transform/TransformSystem.h"
#include "UIOverlay/OverlaySystem.h"

/**
 * Simple context for global systems.
 * @warning Do not use with non-global systems.
 */
struct GameContext {
   // TODO use a player class instead once we have more functinality for it
   std::shared_ptr<PlayerInventoryComponent> player;
   std::shared_ptr<GameScene> scene;
   std::shared_ptr<TransformSystem> transformSystem;
   std::shared_ptr<SpriteSystem> spriteSystem;
   std::shared_ptr<OverlaySystem> overlaySystem;
   //std::shared_ptr<CollisionSystem> collisionSystem;
   std::shared_ptr<ResourceManager> resourceManager;
   std::shared_ptr<InputSystem> inputSystem;
   std::shared_ptr<EventSystem> eventSystem;
   std::shared_ptr<GameMapSystem> gameMapSystem;
   std::shared_ptr<UISystem> uiSystem;
   std::shared_ptr<ItemRegistry> itemRegistry;
   std::shared_ptr<TimeManager> timeManager;
};

#endif //GAME1_GAMECONTEXT_H
