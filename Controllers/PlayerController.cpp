//
// Created by dominik on 15.11.25.
//
#include "PlayerController.h"

PlayerController::PlayerController( GameScene& gameScene ) : scene( gameScene )
{
   mouseCommands[ sf::Mouse::Left ] = ( InputActions{ [this]( const sf::Event& event ) { onLeftClick( event ); },
                                                      []( const sf::Event& event ) { /* release */ } } );
}

void PlayerController::onLeftClick( const sf::Event& event )
{
   scene.handleLeftClick( sf::Vector2f{ (float)event.mouseButton.x, (float)event.mouseButton.y } );
}

