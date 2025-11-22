//
// Created by dominik on 01.11.25.
//

#ifndef GAME1_GAMECONTEXT_H
#define GAME1_GAMECONTEXT_H

#include <memory>
#include "Scene.h"
#include "Collision/CollisionSystem.h"
#include "TextureManager.h"
#include "Input/InputSystem.h"
#include "Event/EventSystem.h"

/**
 * Simple context for global systems.
 * @warning Do not use with non-global systems.
 */
struct GameContext {
   std::shared_ptr<GameScene> scene;
   std::shared_ptr<CollisionSystem> collisionSystem;
   std::shared_ptr<TextureManager> textureManager;
   std::shared_ptr<InputSystem> inputSystem;
   std::shared_ptr<EventSystem> eventSystem;
};

#endif //GAME1_GAMECONTEXT_H
