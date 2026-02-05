//
// Created by dominik on 08.12.25.
//
#include "ResourceCounter.h"
#include "Fonts.h"

ResourceCounter::ResourceCounter( std::string resourceId, float iconSize, const sf::Vector2f& position, float rotation,
                                  bool isVisible ) : UIElement( position, rotation, { 1.f, 1.f }, isVisible ), size( iconSize ),
                                                     resourceId( std::move( resourceId ) )
{
}

void ResourceCounter::onStart( GameContext* context )
{
   auto resourceDef = context->itemRegistry->getDefinition( resourceId );

   if( !resourceDef )
   {
      LOG_WARNING( "Resource definition for resource id: " + resourceId + " not found!" );
   }
   else
   {
      icon.setTexture( context->resourceManager->loadTexture( resourceDef->texturePath ) );
   }
   // Update scale based on icon size so icons can be unified
   auto scale = size / icon.getLocalBounds().width;
   icon.setPosition( getPosition() );
   icon.setRotation( getRotation() );
   localScale = sf::Vector2f( scale, scale );
   icon.setScale( getScale() );

   // Center icon
   icon.setOrigin( icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2 );

   // TODO text isn't automatically centered, implement own extension of sfml text
   // Add a text component and add it as a child. Position is size / 2 + 4 since the icon is centered, and we add 4 pixels of space
   textComponent = std::make_shared<UIElementText>( Fonts::mainFont, "0", 18, sf::Color::White,
                                                    sf::Vector2f{ -12.f, size / 2 - 5.f } );
   addChild( textComponent );

   // Base class onStart which call onStart of children
   UIElement::onStart( context );
}

void ResourceCounter::updateCounterAmount( unsigned int newAmount ) const
{
   textComponent->setText( std::to_string( newAmount ) );
}

void ResourceCounter::draw( sf::RenderTarget& target, const Renderer& renderer )
{
   renderer.render( icon, target );
   UIElement::draw( target, renderer );
}

const std::string& ResourceCounter::getCountedItemId() const
{
   return resourceId;
}
