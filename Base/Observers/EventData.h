//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_EVENTDATA_H
#define GAME1_EVENTDATA_H

#include <variant>
#include <SFML/System/Vector2.hpp>

struct CollisionEventData
{
   sf::Vector2f location;
};

struct ScoreboardUpdateEventData
{
   explicit ScoreboardUpdateEventData( size_t pts ) : points( pts )
   {
   };

   size_t points;
};

using EventData = std::variant<ScoreboardUpdateEventData, CollisionEventData>;
#endif //GAME1_EVENTDATA_H
