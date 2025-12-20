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
        Base/ResourceManager.h
        Base/ResourceManager.cpp
        Base/GameMap/MapTile.h
        Base/GameMap/MapTile.cpp
        Base/GameMap/GameMap.h
        Base/GameMap/GameMap.cpp
        Base/Input/InputSystem.h
        Base/Input/InputSystem.cpp
        Base/Input/Controller.cpp
        Base/Input/InputActions.h
        Src/Controllers/PlayerController.h
        Src/Controllers/PlayerController.cpp
        Base/Input/Clickable.h
        Base/Core/Mobility.h
        Base/UI/UIBlock.h
        Base/UI/UIBlock.cpp
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
        Src/Entities/Buildings/BuildingType.h
        Src/Entities/Buildings/BuildingFactory.h
        Src/Entities/Buildings/Building.h
        Src/Entities/Buildings/BuildingFactory.cpp
        Src/Entities/Buildings/Concrete/PeasantHouse.h
        Src/Entities/Buildings/Concrete/PeasantHouse.cpp
        Src/Entities/Buildings/Building.cpp
        Src/Entities/Buildings/BuildingPlacementButton.h
        Src/Entities/Buildings/BuildingEvents.h
        Base/Core/SpawnCategory.h
        Base/UI/UISystem.h
        Base/GameMap/GameMapSystem.h
        Base/GameMap/GameMapSystem.cpp
        Base/UI/UISystem.cpp
        Base/Data/ItemDefinition.h
        Base/Data/ItemRegistry.h
        Base/Data/ItemRegistry.cpp
        Base/Data/ItemInstance.h
        Base/Data/InventoryComponent.h
        Base/Data/InventoryComponent.cpp
        Base/Data/ItemInstance.cpp
        Base/Player.h
        Src/GameItems.h
        Src/UI/ResourceBar.h
        Src/UI/ResourceCounter.h
        Src/UI/Fonts.h
        Src/UI/ResourceCounter.cpp
        Src/UI/ResourceBar.cpp
        Base/Data/PlayerInventoryComponent.h
        Base/Data/ItemEvents.h
        Base/Data/PlayerInventoryComponent.cpp
        Src/GameItemRegistry.h
        Src/GameItemRegistry.cpp
        Base/Time/TimerHandle.h
        Base/Time/Timer.h
        Base/Time/TimeManager.h
        Base/Time/Timer.cpp
        Base/Time/TimerHandle.cpp
        Base/Time/TimeManager.cpp
        Base/Logging/Logger.h
        Base/Logging/Logger.cpp
        Src/Entities/ResourceActor.h
        Src/Entities/ResourceActor.cpp
        Src/Entities/ResourceFactory.h
        Src/Entities/ResourceFatory.cpp
        Src/Entities/Buildings/Concrete/StoneMiner.h
        Src/Entities/Buildings/Concrete/StoneMiner.cpp
)


# Find SFML library package
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Link SFML libraries to the target
target_link_libraries(game1 sfml-graphics sfml-window sfml-system)
