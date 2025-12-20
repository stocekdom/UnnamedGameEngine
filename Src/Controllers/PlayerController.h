//
// Created by dominik on 15.11.25.
//

#ifndef GAME1_PLAYERCONTROLLER_H
#define GAME1_PLAYERCONTROLLER_H

#include "../../Base/Input/Controller.h"
#include "../../Base/GameContext.h"
#include "../Entities/Buildings/BuildingEvents.h"
#include "../../Base/Event/Events.h"
#include "../Entities/Buildings/Building.h"
#include <memory>

class PlayerController : public Controller
{
   public:
      explicit PlayerController( const std::shared_ptr<GameContext>& context );

      void tick( float dt ) override;

   protected:
      void onLeftClick( const ActionData& event ) const;

      void onMouseMove( const sf::Vector2i& position );

      void onPauseGame( const GamePaused& event );

      void onResumeGame( const GameResumed& event );

      void onBuildingPlacingStart( const BuildingPlacingStarted& event );

      void onBuildingPlacingCancel();

      void onBuildingPlaced( const sf::Vector2i& position );

      void updateCameraSpeedX( float x );

      void updateCameraSpeedY( float y );

      void updateCameraZoom( float zoom );

   private:
      // Predefined colors for building coloring when placing
      static inline const sf::Color DefaultOverlay = sf::Color( 255, 255, 255, 216 );
      static inline const sf::Color RedOverlay = sf::Color( 255, 128, 128, 216 );
      static inline const sf::Color GreenOverlay = sf::Color( 128, 255, 128, 216 );

      sf::Vector2f cameraSpeed;
      // Speed of camera movement since the camera speed vector is normalized.
      static constexpr float CAMERA_SPEED = 500.f;
      // A distance between targetZoom and currentZoom that will trigger currentZoom changing directly to targetZoom.
      static constexpr float SNAP_THRESHOLD = 0.01f;
      static constexpr float MAX_ZOOM = 3.5f;
      static constexpr float MIN_ZOOM = 0.5f;
      static constexpr float ZOOM_STEP = 0.3f;
      static constexpr float ZOOM_PER_SECOND = 6.f;
      float currentZoom = 1.f;
      float targetZoom = 1.f;
      std::shared_ptr<InputContext> menuContext;
      std::shared_ptr<InputContext> mainContext;
      std::shared_ptr<InputContext> placingContext;
      GameContext* context;
      std::weak_ptr<Building> buildingPawn;
      // Flag to optimize placing. If we remember last state we only have to call setColor of the sprite on state change
      bool previousBuildingPlacingState = false;

      void movePawnFromOverlayToWorld( const std::shared_ptr<Building>& building );
};

#endif //GAME1_PLAYERCONTROLLER_H
