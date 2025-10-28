//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_SCOREBOARD_H
#define GAME1_SCOREBOARD_H

#include <SFML/Graphics/Text.hpp>
#include "../Base/Entity/UIElementText.h"
#include "../Base/Observers/Subject.h"

class Scoreboard : public UIElementText
{
   public:
      explicit Scoreboard( const std::string& fontPath, const std::string& inText, int size = 16, sf::Color color = sf::Color::Black, sf::Vector2f position = { 0, 0 },
                  float rotation = 0, sf::Vector2f scale = { 1, 1 } );

      void addScore( size_t amount );

      void reduceScore( size_t amount );

      [[nodiscard]] std::size_t getScore() const;

   private:

      void updateText();

      std::size_t score;
};

#endif //GAME1_SCOREBOARD_H
