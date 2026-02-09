//
// Created by dominik on 07.02.26.
//

#ifndef GAME1_MAPGENERATOR_H
#define GAME1_MAPGENERATOR_H

#include <queue>

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
      static constexpr float edgeLandProbability = 0.3f;
      static constexpr int automataIterations = 3;
      static constexpr int continents = 2;
      // Sets the minimum point for the split point as the percentage of the whole width/height
      static constexpr float splitMinPercentage = 0.35f;
      // Sets the maximum point for the split point as the percentage of the whole width/height
      static constexpr float splitMaxPercentage = 0.65f;
      static constexpr int maxLandNeighbors = 4;
      static constexpr int maxWaterNeighbors = 5;
      static constexpr int waterEdge = 1;
      // Sets the distance from chunk edge where land use edgeLandProbability
      static constexpr int sparseLands = 3;

      using Chunk = sf::IntRect;

      void cellularAutomataSmoothing( std::vector<Tile>& map, const std::vector<Chunk>& chunks ) const;

      void cellularAutomateImpl( std::vector<Tile>& map, const std::vector<Chunk>& chunks ) const;

      /**
       * Generates split points for the map using binary space partition. Inside these chunks, continents can be generated
       * @return Vector of chunks which are just SFML int rectangles
       */
      std::vector<Chunk> generateMapChunks();

      [[nodiscard]] bool shouldVerticalSplit( const Chunk& chunk );

      [[nodiscard]] int countNeighborsOfType( const std::vector<Tile>& map, const Chunk& chunk, int x, int y,
                                              TileType type ) const;

      /**
       * Gets blobs of land, which are basically graph components. Also prunes blobs that are too small and can't be a region
       * Can be used to determine chunks of land and either prune them or generate regions on them
       * @param map The world map
       * @return Vector of land blobs
       */
      std::vector<std::vector<int>> getAndPruneLandBlobs( std::vector<Tile>& map ) const;

      /**
       * Gets the list of generated regions and merges regions that are smaller than minRegionSize with the nearest neighboring region
       * @note If a region doesn't have a neighbor, nothing happens. However this only happens if a region is on an island and doesn't have enough tiles, which should not happen if calling getAndPruneLandBlobs before calling this method
       * @param map
       * @param regions
       */
      void mergeSmallRegions( std::vector<Tile>& map, std::vector<Region>& regions ) const;

      /**
       * Returns the smallest neighbor of the region with regionIndex based on size
       * @param map World map
       * @param regions List of all regions
       * @param regionIndex Region to find the neighbor for
       * @return Index of the chosen neighbor
       */
      [[nodiscard]] unsigned int getSmallestRegionNeighbor( const std::vector<Tile>& map, const std::vector<Region>& regions,
                                                            unsigned int regionIndex ) const;

      /**
       * Samples the land blob and creates seed points for regions using Poisson Disk Sampling.
       * @param blob Blob to sample. The blob gets shuffled
       * @param amount Number of points to sample
       * @return A vector of sampled points for BFS processing
       */
      std::vector<int> samplePointsAndRegions( std::vector<int>& blob, int amount );
};

#endif //GAME1_MAPGENERATOR_H
