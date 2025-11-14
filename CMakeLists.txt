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
        Controllers/IController.h
        Controllers/Commands/Command.h
        Base/Collision/ICollider.h
        Base/Collision/CollisionInfo.h
        Base/Collision/CollisionSystem.h
        Base/Collision/ICollider.cpp
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
        Base/Entity/UIElement.h
        Base/Entity/SpacialEntity.h
        Base/Entity/UIElementText.h
        Base/Entity/UIElementText.cpp
        Base/Utility/Math.h
        Base/Entity/SpacialEntity.cpp
        Base/Entity/Entity.cpp
        Base/Entity/UIElement.cpp
        Base/Collision/Collidable.h
        Base/Collision/ColliderType.h
        Base/Utility/CollisionHelper.h
        Base/GameContext.h
        Base/Entity/IsometricActor.h
        Base/Entity/IsometricActor.cpp
        Base/TextureManager.h
        Base/TextureManager.cpp
        Entities/MapTile.h
        Entities/MapTile.cpp
        Entities/GameMap.h
        Entities/GameMap.cpp
)


# Find SFML library package
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Link SFML libraries to the target
target_link_libraries(game1 sfml-graphics sfml-window sfml-system)
