//
// Created by dominik on 07.02.26.
//

#ifndef GAME1_TILETYPES_H
#define GAME1_TILETYPES_H

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <vector>

enum class TileType : std::uint8_t { Water = 0, Land = 1 };

// Here we use vector2i for convenience, but internally we use unsigned int since the array is 1D
using TileIndex = sf::Vector2i;

struct Tile
{
   TileType type;
   // This doesn't have to be here since regions will have tile vector, but it allows for easier region access
   unsigned int regionId;
};

struct Region
{
   // Regions ids start from 1. 0 means unassigned region
   unsigned int id = 0;
   bool invalid = false;
   bool isOwned = false;
   // bool
   // bool
   // 2 bools max to fit the alignment. More data increases the Region size
   // Unsigned int represents the tile in a map represented as a 1D vector. Basically index = x + y * width
   std::vector<int> tiles;
};
#endif //GAME1_TILETYPES_H