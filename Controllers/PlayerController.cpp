//
// Created by dominik on 15.11.25.
//
#include "PlayerController.h"
#include "../Base/Core/Math.h"
#include "../Base/Input/ContextFactory.h"

// We initialize everything in the constructor since systems are already created at this point, and we don't need onStart
PlayerController::PlayerController( const std::shared_ptr<GameContext>& context ) : scene( context->scene ),
                                                                                    cameraSpeed( 0.f, 0.f )
{
   context->eventSystem->subscribe<GamePaused>( [this]( const GamePaused& event ) { onPauseGame( event ); } );
   context->eventSystem->subscribe<GameResumed>( [this]( const GameResumed& event ) { onResumeGame( event ); } );
   menuContext = ContextFactory::createMenuContext();
   mainContext = ContextFactory::createGameContext();
   activeContext = mainContext;
   actions[ GameAction::LEFT_CLICK ] = [this]( const ActionData& event ) {
      if( event.isPressed )
         onLeftClick( event );
   };
   actions[ GameAction::CAMERA_MOVE_RIGHT ] = [this]( const ActionData& event ) {
      event.isPressed ? updateCameraSpeedX( 1.0f ) : updateCameraSpeedX( 0.f );
   };
   actions[ GameAction::CAMERA_MOVE_LEFT ] = [this]( const ActionData& event ) {
      event.isPressed ? updateCameraSpeedX( -1.0f ) : updateCameraSpeedX( 0.f );
   };
   actions[ GameAction::CAMERA_MOVE_UP ] = [this]( const ActionData& event ) {
      event.isPressed ? updateCameraSpeedY( -1.0f ) : updateCameraSpeedY( 0.f );
   };
   actions[ GameAction::CAMERA_MOVE_DOWN ] = [this]( const ActionData& event ) {
      event.isPressed ? updateCameraSpeedY( 1.0f ) : updateCameraSpeedY( 0.f );
   };
   actions[ GameAction::CAMERA_ZOOM ] = [this]( const ActionData& event ) { updateCameraZoom( event.value ); };
}

void PlayerController::tick( float dt )
{
   if( cameraSpeed.x != 0.f || cameraSpeed.y != 0.f )
      scene->moveCamera( cameraSpeed * CAMERA_SPEED * dt );

   if( targetZoom != currentZoom )
   {
      float prevZoom = currentZoom;
      float delta = targetZoom - currentZoom;
      float change = dt * ZOOM_PER_SECOND;

      if( delta < 0 )
         currentZoom = std::max( targetZoom, currentZoom - change );
      else
         currentZoom = std::min( targetZoom, currentZoom + change );

      scene->zoomCamera( currentZoom / prevZoom );
   }
}

void PlayerController::onLeftClick( const ActionData& event )
{
   scene->onLeftClick( event.position );
}

void PlayerController::onPauseGame( const GamePaused& event )
{
   activeContext = menuContext;
}

void PlayerController::onResumeGame( const GameResumed& event )
{
   activeContext = mainContext;
}

void PlayerController::updateCameraSpeedX( float x )
{
   cameraSpeed.x = x;
   cameraSpeed = Math::normalize( cameraSpeed );
}

void PlayerController::updateCameraSpeedY( float y )
{
   cameraSpeed.y = y;
   cameraSpeed = Math::normalize( cameraSpeed );
}

void PlayerController::updateCameraZoom( float zoom )
{
   if( zoom > 0.f )
      targetZoom *= ( 1.f - ZOOM_STEP ); // Zoom in
   else
      targetZoom *= ( 1.f + ZOOM_STEP ); // Zoom out

   targetZoom = std::clamp( targetZoom, MIN_ZOOM, MAX_ZOOM );
}
