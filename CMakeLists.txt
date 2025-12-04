cmake_minimum_required(VERSION 3.28)
project(game1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(game1 main.cpp
        Base/Scene.h
        Base/Entity/Actor.h
        Base/Entity/Actor.cpp
        Base/Scene.cpp
        Base/Game.h
        Base/Renderer.h
        Base/Renderer.cpp
        Base/Game.cpp
        Base/Input/Controller.h
        Base/Collision/Collider.h
        Base/Collision/CollisionInfo.h
        Base/Collision/CollisionSystem.h
        Base/Collision/Collider.cpp
        Base/Collision/ColliderRect.h
        Base/Collision/ColliderPoint.h
        Base/Collision/ColliderRect.cpp
        Base/Collision/ColliderPoint.cpp
        Base/Collision/CollisionSystem.cpp
        Base/Observers/Subject.h
        Base/Observers/Observer.h
        Base/Observers/Subject.cpp
        Base/Observers/EventData.h
        Base/Entity/Entity.h
        Base/UI/UIElement.h
        Base/Entity/SpacialEntity.h
        Base/UI/UIElementText.h
        Base/UI/UIElementText.cpp
        Base/Core/Math.h
        Base/Entity/SpacialEntity.cpp
        Base/Entity/Entity.cpp
        Base/UI/UIElement.cpp
        Base/Collision/Collidable.h
        Base/Collision/ColliderType.h
        Base/Collision/CollisionHelper.h
        Base/GameContext.h
        Base/Entity/IsometricActor.h
        Base/Entity/IsometricActor.cpp
        Base/TextureManager.h
        Base/TextureManager.cpp
        Entities/MapTile.h
        Entities/MapTile.cpp
        Entities/GameMap.h
        Entities/GameMap.cpp
        Base/Input/InputSystem.h
        Base/Input/InputSystem.cpp
        Base/Input/Controller.cpp
        Base/Input/InputActions.h
        Controllers/PlayerController.h
        Controllers/PlayerController.cpp
        Base/Input/Clickable.h
        Base/Core/Mobility.h
        Base/UI/UIBlock.h
        Base/UI/UIBlock.cpp
        Entities/ClickableText.h
        Entities/ClickableText.cpp
        Base/Event/EventSystem.h
        Base/Event/CallbackContainer.h
        Base/Event/Events.h
        Base/UI/UIRoot.h
        Base/UI/UIRoot.cpp
        Base/UI/UIButton.h
        Base/Input/InputContext.h
        Base/Input/InputEventKey.h
        Base/Input/GameAction.h
        Base/Input/InputContext.cpp
        Base/Input/ContextFactory.h
        Base/Input/ContextFactory.cpp
        Base/Core/Math.cpp
        Base/Core/UUID.h
        Base/Core/UUID.cpp
        Entities/Buildings/BuildingType.h
        Entities/Buildings/BuildingFactory.h
        Entities/Buildings/Building.h
        Entities/Buildings/BuildingFactory.cpp
        Entities/Buildings/PeasantHouse.h
        Entities/Buildings/PeasantHouse.cpp
        Entities/Buildings/Building.cpp
        Entities/Buildings/BuildingPlacementButton.h
        Entities/Buildings/BuildingEvents.h
        Base/Core/SpawnCategory.h
)


# Find SFML library package
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Link SFML libraries to the target
target_link_libraries(game1 sfml-graphics sfml-window sfml-system)
