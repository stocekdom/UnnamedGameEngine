//
// Created by dominik on 27.11.25.
//

#ifndef GAME1_GAMEACTION_H
#define GAME1_GAMEACTION_H

enum class GameAction
{
   NONE,
   CAMERA_MOVE_LEFT,
   CAMERA_MOVE_RIGHT,
   CAMERA_MOVE_UP,
   CAMERA_MOVE_DOWN,
   CAMERA_ZOOM,
   LEFT_CLICK,
   MOUSE_MOVE,
   PLACE_BUILDING,
   PLACEMENT_CANCEL,
};

struct ActionData
{
   // Value for analog actions.
   float value = 0;
   sf::Vector2i position = { 0, 0 };
};
#endif //GAME1_GAMEACTION_H
