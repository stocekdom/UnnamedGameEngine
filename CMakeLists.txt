cmake_minimum_required(VERSION 3.28)
project(game1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_library(engine
        Engine/Scene.h
        Engine/Entity/Actor.h
        Engine/Entity/Actor.cpp
        Engine/Scene.cpp
        Engine/Game.h
        Engine/Renderer.h
        Engine/Renderer.cpp
        Engine/Game.cpp
        Engine/Input/Controller.h
        Engine/Collision/CollisionInfo.h
        Engine/Collision/CollisionSystem.h
        Engine/Collision/CollisionSystem.cpp
        Engine/Observers/Subject.h
        Engine/Observers/Observer.h
        Engine/Observers/Subject.cpp
        Engine/Observers/EventData.h
        Engine/UI/UIElement.h
        Engine/UI/UIElementText.h
        Engine/UI/UIElementText.cpp
        Engine/Core/Math.h
        Engine/UI/UIElement.cpp
        Engine/Collision/Collidable.h
        Engine/Collision/ColliderType.h
        Engine/Collision/CollisionHelper.h
        Engine/GameContext.h
        Engine/ResourceManager.h
        Engine/ResourceManager.cpp
        Engine/Input/InputSystem.h
        Engine/Input/InputSystem.cpp
        Engine/Input/Controller.cpp
        Engine/Input/Clickable.h
        Engine/UI/UIBlock.h
        Engine/UI/UIBlock.cpp
        Engine/Event/EventSystem.h
        Engine/Event/CallbackContainer.h
        Engine/Event/Events.h
        Engine/UI/UIRoot.h
        Engine/UI/UIRoot.cpp
        Engine/UI/UIButton.h
        Engine/Input/InputContext.h
        Engine/Input/InputEventKey.h
        Engine/Input/GameAction.h
        Engine/Input/InputContext.cpp
        Engine/Input/ContextFactory.h
        Engine/Input/ContextFactory.cpp
        Engine/Core/Math.cpp
        Engine/UI/UISystem.h
        Engine/UI/UISystem.cpp
        Engine/Data/ItemDefinition.h
        Engine/Data/ItemRegistry.h
        Engine/Data/ItemRegistry.cpp
        Engine/Data/ItemInstance.h
        Engine/Data/InventoryComponent.h
        Engine/Data/ItemInstance.cpp
        Engine/Player.h
        Engine/Data/ItemEvents.h
        Engine/Time/TimerComponent.h
        Engine/Time/TimeSystem.h
        Engine/Time/TimeSystem.cpp
        Engine/Logging/Logger.h
        Engine/Logging/Logger.cpp
        Engine/EntityManager.h
        Engine/EntityManager.cpp
        Engine/Entity.h
        Engine/ComponentContainer.h
        Engine/ComponentRegistry.h
        Engine/Entity/FunctionalEntity.h
        Engine/Transform/TransformComponent.h
        Engine/Transform/TransformSystem.h
        Engine/Transform/TransformSystem.cpp
        Engine/ComponentSystem.h
        Engine/Core/Util.h
        Engine/Sprite/SpriteSystem.h
        Engine/Sprite/SpriteRenderProxy.h
        Engine/Sprite/SpriteSystem.cpp
        Engine/Entity/SpriteActor.h
        Engine/Entity/SpriteActor.cpp
        Engine/Sprite/SpriteComponent.h
        Engine/UIOverlay/OverlaySystem.h
        Engine/UIOverlay/OverlaySystem.cpp
        Engine/UIOverlay/OverlaySpriteComponent.h
        Engine/Sprite/SpriteMobility.h
        Engine/System.h
        Engine/Input/UIController.h
        Engine/Input/UIController.cpp
        Engine/Data/InventorySystem.h
        Engine/Data/InventorySystem.cpp
        Engine/Tags/TagSystem.h
        Engine/Tags/Tags.h
        Engine/Tags/TagSystem.cpp
        Engine/JSON/JSONTypes.h
        Engine/JSON/JSONParser.h
        Engine/JSON/JSONParser.cpp
        Engine/JSON/JSONTokenizer.h
        Engine/JSON/JSONTokenizer.cpp
)


# Find SFML library package
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Link SFML libraries to the target
target_link_libraries(engine sfml-graphics sfml-window sfml-system)

add_executable(game main.cpp)
target_link_libraries(game engine)

add_executable(engineTests Tests/TestMain.cpp
        Tests/TestFramework.h
        Tests/JSON/TokenizerTests.cpp
        Tests/JSON/ParserTests.cpp
)

target_link_libraries(engineTests engine)

enable_testing()

add_test(NAME engine_tests COMMAND engineTests)
