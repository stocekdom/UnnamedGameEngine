//
// Created by dominik on 07.02.26.
//

#ifndef GAME1_MAPGENERATOR_H
#define GAME1_MAPGENERATOR_H

#include "TileTypes.h"
#include <SFML/Graphics/Rect.hpp>
#include <random>

class MapTile;

class MapGenerator
{
   public:
      MapGenerator( size_t seed );

      /**
       * Generates the map as an enum of tiles. Doesn't add anything to the scene, nor does it generate a map of entity classes
       * @param mapWidth Map width
       * @param mapHeight Map height
       * @return Vector of tiles representing the map. Size is width * height
       */
      std::vector<Tile> generateMap( int mapWidth, int mapHeight );

   private:
      std::mt19937 rng;
      std::uniform_real_distribution<float> floatDist;
      std::uniform_int_distribution<> bitDistribution;
      int width;
      int height;

      // TODO add to config file
      static constexpr float landProbability = 0.52f;
      static constexpr float edgeLandProbability = 0.35f;
      static constexpr int automataIterations = 2;
      static constexpr int continents = 2;
      // Sets the minimum point for the split point as the percentage of the whole width/height
      static constexpr float splitMinPercentage = 0.35f;
      // Sets the maximum point for the split point as the percentage of the whole width/height
      static constexpr float splitMaxPercentage = 0.65f;
      static constexpr int maxLandNeighbors = 4;
      static constexpr int maxWaterNeighbors = 4;
      static constexpr int waterEdge = 1;
      // Sets the distance from chunk edge where land use edgeLandProbability
      static constexpr int sparseLands = 3;

      using Chunk = sf::IntRect;

      void cellularAutomataSmoothing( std::vector<Tile>& map, const std::vector<Chunk>& chunks ) const;

      void cellularAutomateImpl( std::vector<Tile>& map, const Chunk& chunk ) const;

      /**
       * Generates split points for the map using binary space partition. Inside these chunks, continents can be generated
       * @return Vector of chunks which are just SFML int rectangles
       */
      std::vector<Chunk> generateMapChunks();

      [[nodiscard]] bool shouldVerticalSplit( const Chunk& chunk );

      [[nodiscard]] int countNeighborsOfType( const std::vector<Tile>& map, const Chunk& chunk, int x, int y, Tile type ) const;
};

#endif //GAME1_MAPGENERATOR_H
