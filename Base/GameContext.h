//
// Created by dominik on 01.11.25.
//

#ifndef GAME1_GAMECONTEXT_H
#define GAME1_GAMECONTEXT_H

#include <memory>
#include "Scene.h"
#include "ResourceManager.h"
#include "../Src/GameItemRegistry.h"
#include "Input/InputSystem.h"
#include "Event/EventSystem.h"
#include "UI/UISystem.h"
#include "GameMap/GameMapSystem.h"
#include "Data/PlayerInventoryComponent.h"
#include "Sprite/SpriteSystem.h"
#include "Tags/TagSystem.h"
#include "Time/TimeSystem.h"
#include "Transform/TransformSystem.h"
#include "UIOverlay/OverlaySystem.h"

/**
 * Simple context for global systems.
 * @warning Do not use with non-global systems.
 */
struct GameContext
{
   GameContext()
      : player( std::make_shared<PlayerInventoryComponent>() ),
        scene( std::make_shared<GameScene>() ),
        transformSystem( std::make_shared<TransformSystem>() ),
        spriteSystem( std::make_shared<SpriteSystem>() ),
        overlaySystem( std::make_shared<OverlaySystem>() ),
        resourceManager( std::make_shared<ResourceManager>() ),
        inputSystem( std::make_shared<InputSystem>() ),
        eventSystem( std::make_shared<EventSystem>() ),
        gameMapSystem( std::make_shared<GameMapSystem>() ),
        uiSystem( std::make_shared<UISystem>() ),
        itemRegistry( std::make_shared<GameItemRegistry>() ),
        timeManager( std::make_shared<TimeSystem>() ),
        tagSystem( std::make_shared<TagSystem>() )
   {
   }

   // TODO use a player class instead once we have more functinality for it
   const std::shared_ptr<PlayerInventoryComponent> player;
   const std::shared_ptr<GameScene> scene;
   const std::shared_ptr<TransformSystem> transformSystem;
   const std::shared_ptr<SpriteSystem> spriteSystem;
   const std::shared_ptr<OverlaySystem> overlaySystem;
   //std::shared_ptr<CollisionSystem> collisionSystem;
   const std::shared_ptr<ResourceManager> resourceManager;
   const std::shared_ptr<InputSystem> inputSystem;
   const std::shared_ptr<EventSystem> eventSystem;
   const std::shared_ptr<GameMapSystem> gameMapSystem;
   const std::shared_ptr<UISystem> uiSystem;
   const std::shared_ptr<ItemRegistry> itemRegistry;
   const std::shared_ptr<TimeSystem> timeManager;
   const std::shared_ptr<TagSystem> tagSystem;
};

#endif //GAME1_GAMECONTEXT_H
