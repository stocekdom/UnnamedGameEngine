//
// Created by dominik on 08.12.25.
//

#ifndef GAME1_RESOURCECOUNTER_H
#define GAME1_RESOURCECOUNTER_H

#include <SFML/Graphics/Sprite.hpp>
#include "../../Base/UI/UIElementText.h"

class ResourceCounter : public UIElement
{
   public:
      ResourceCounter( std::string resourceId, float iconSize, const sf::Vector2f& position = { 0.f, 0.f }, float rotation = 0,
                       bool isVisible = true );

      void onStart( GameContext* context ) override;

      void draw( sf::RenderTarget& target, const Renderer& renderer ) override;

      void updateCounterAmount( unsigned int newAmount ) const;

      const std::string& getCountedItemId() const;

   private:
      float size;
      std::shared_ptr<UIElementText> textComponent;
      std::string resourceId;
      sf::Sprite icon;
};

#endif //GAME1_RESOURCECOUNTER_H
