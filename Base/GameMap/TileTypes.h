//
// Created by dominik on 07.02.26.
//

#ifndef GAME1_TILETYPES_H
#define GAME1_TILETYPES_H

#include <cstdint>
#include <vector>

enum class TileType : std::uint8_t { Water = 0, Land = 1 };

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
   // Unsigned int represents the tile in a map represented as a 1D vector. Basically index = x + y * width
   std::vector<int> tiles;
};
#endif //GAME1_TILETYPES_H