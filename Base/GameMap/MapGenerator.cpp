//
// Created by dominik on 07.02.26.
//

#include "MapGenerator.h"
#include "../Core/Math.h"
#include "../Core/Util.h"
#include "../../Src/GameItems.h"
#include "../Logging/Logger.h"
#include "MapTile.h"
#include "../../Src/Entities/ResourceFactory.h"
#include <queue>

// Setting distributions like this is slower and wasteful.
// If performance is an issue> https://martin.ankerl.com/2018/12/08/fast-random-bool/
MapGenerator::MapGenerator() : floatDist( 0, 1 ), bitDistribution( 0, 1 )
{
}

std::vector<Tile> MapGenerator::generateMap( int mapWidth, int mapHeight, std::mt19937& rng )
{
   std::vector<Tile> map( mapWidth * mapHeight );
   width = mapWidth;
   height = mapHeight;

   auto chunks = generateMapChunks( rng );

   // Loops start from chunk + waterEdge to leave water tiles on the edges
   for( const auto& chunk: chunks )
      for( int x = chunk.top + waterEdge; x < chunk.top + chunk.height - waterEdge; ++x )
         for( int y = chunk.left + waterEdge; y < chunk.left + chunk.width - waterEdge; ++y )
         {
            if( x < chunk.top + waterEdge + sparseLands || x >= chunk.top + chunk.height - waterEdge - sparseLands ||
                y < chunk.left + waterEdge + sparseLands || y >= chunk.left + chunk.width - waterEdge - sparseLands )
               map[ Math::coordsToIndex( x, y, mapWidth ) ].type = floatDist( rng ) <= edgeLandProbability
                                                                      ? TileType::Land
                                                                      : TileType::Water;
            else
               map[ Math::coordsToIndex( x, y, mapWidth ) ].type = floatDist( rng ) <= landProbability
                                                                      ? TileType::Land
                                                                      : TileType::Water;
         }

   cellularAutomataSmoothing( map, chunks );
   return map;
}

std::vector<Region> MapGenerator::generateRegions( std::vector<Tile>& map, int mapWidth, int mapHeight, std::mt19937& rng )
{
   auto landBlobs = getAndPruneLandBlobs( map );
   std::vector<Region> regions;
   // Offsets for the neighbors
   int offsets[ 4 ] = { -1, +1, -width, +width };
   std::queue<int> tilesToProcess;

   // Initial seed tiles for each blob.
   // ReSharper disable once CppDFAUnreadVariable
   unsigned int regionNum = 0;
   for( auto& blob: landBlobs )
   {
      // The amount of sampled points to ensure large blobs don't have that many regions, but the islands that have at least minRegionSize get their own region and don't get pruned
      auto samples = samplePointsAndRegions( blob, std::ceil( blob.size() / ( minRegionSize * 4 ) ), rng );

      // For the sampled points make regions and add them to the sampled tiles
      for( auto sample: samples )
      {
         regions.emplace_back( Region{ ++regionNum, {} } );
         map[ sample ].regionId = regions.back().id;
         tilesToProcess.push( sample );
         regions.back().tiles.push_back( sample );
      }
   }

   // Flood fill from seed points. BFS
   while( !tilesToProcess.empty() )
   {
      int idx = tilesToProcess.front();
      tilesToProcess.pop();

      for( const int offset: offsets )
      {
         int neighbor = idx + offset;
         // The check can probably be done with only the neighbor. This is just to be safe
         auto coords = Math::indexToCoords( neighbor, mapWidth );

         if( coords.x < 0 || coords.x >= height || coords.y < 0 || coords.y >= width )
            continue;

         if( map[ neighbor ].regionId == 0 && map[ neighbor ].type == TileType::Land )
         {
            map[ neighbor ].regionId = map[ idx ].regionId;
            regions[ map[ idx ].regionId - 1 ].tiles.push_back( neighbor );
            tilesToProcess.push( neighbor );
         }
      }
   }

   // This leaves some regions invalid, but they remain in the vector. Should be fine since we usually have a small number of regions
   // If this becomes a problem, implement a way to prune invalid regions and reorder the rest
   mergeSmallRegions( map, regions );
   return regions;
}

void MapGenerator::cellularAutomataSmoothing( std::vector<Tile>& map, const std::vector<Chunk>& chunks ) const
{
   for( int i = 0; i < automataIterations; ++i )
      cellularAutomateImpl( map, chunks );
}

void MapGenerator::cellularAutomateImpl( std::vector<Tile>& map, const std::vector<Chunk>& chunks ) const
{
   std::vector<Tile> buffer( map.size() );

   for( const auto& chunk: chunks )
   {
      for( int x = chunk.top; x < chunk.top + chunk.height; ++x )
      {
         for( int y = chunk.left; y < chunk.left + chunk.width; ++y )
         {
            switch( map[ Math::coordsToIndex( x, y, width ) ].type )
            {
               case TileType::Water:
               {
                  auto landNeighbors = countNeighborsOfType( map, chunk, x, y, TileType::Land );
                  buffer[ Math::coordsToIndex( x, y, width ) ].type = landNeighbors > maxLandNeighbors
                                                                         ? TileType::Land
                                                                         : TileType::Water;
                  break;
               }
               case TileType::Land:
               {
                  auto waterNeighbors = countNeighborsOfType( map, chunk, x, y, TileType::Water );
                  buffer[ Math::coordsToIndex( x, y, width ) ].type = waterNeighbors > maxWaterNeighbors
                                                                         ? TileType::Water
                                                                         : TileType::Land;
                  break;
               }
            }
         }
      }
   }

   std::swap( map, buffer );
}

std::vector<MapGenerator::Chunk> MapGenerator::generateMapChunks( std::mt19937& rng )
{
   std::vector<Chunk> chunks;
   // Initial whole map
   chunks.emplace_back( 0, 0, static_cast<int>( width ), static_cast<int>( height ) );
   std::queue<size_t> chunkIndicesToProcess;
   chunkIndicesToProcess.push( 0 );

   for( int i = 1; i < continents; ++i )
   {
      auto index = chunkIndicesToProcess.front();
      chunkIndicesToProcess.pop();

      bool splitVertical = chunks[ index ].width > chunks[ index ].height;
      float splitPoint = splitMinPercentage + ( floatDist( rng ) * ( splitMaxPercentage - splitMinPercentage ) );

      Chunk newChunk;

      if( splitVertical )
      {
         int splitWidth = static_cast<int>( chunks[ index ].width * splitPoint );
         newChunk = Chunk( chunks[ index ].left + splitWidth, chunks[ index ].top, chunks[ index ].width - splitWidth,
                           chunks[ index ].height );
         chunks[ index ].width -= splitWidth;
      }
      else
      {
         int splitHeight = static_cast<int>( chunks[ index ].height * splitPoint );
         newChunk = Chunk( chunks[ index ].left, chunks[ index ].top + splitHeight, chunks[ index ].width,
                           chunks[ index ].height - splitHeight );
         chunks[ index ].height -= splitHeight;
      }

      // Trivially copyable
      chunks.emplace_back( newChunk );

      // Process the larger chunk first
      if( splitPoint > 0.5f )
      {
         chunkIndicesToProcess.push( index );
         chunkIndicesToProcess.push( i );
      }
      else
      {
         chunkIndicesToProcess.push( i );
         chunkIndicesToProcess.push( index );
      }
   }

   return chunks;
}

bool MapGenerator::shouldVerticalSplit( const Chunk& chunk, std::mt19937& rng )
{
   if( chunk.width == chunk.height )
      return bitDistribution( rng );

   return chunk.width > chunk.height;
}

int MapGenerator::countNeighborsOfType( const std::vector<Tile>& map, const Chunk& chunk, int x, int y, TileType type ) const
{
   int count = 0;

   // X is the row, Y is the column. !!! Different from screen coordinates
   // Limit the iteration constants to the chunk bounds
   for( int i = std::max( chunk.top, x - 1 ); i <= std::min( chunk.top + chunk.height - 1, x + 1 ); ++i )
      for( int j = std::max( chunk.left, y - 1 ); j <= std::min( chunk.left + chunk.width - 1, y + 1 ); ++j )
         if( ( i != x || j != y ) && map[ Math::coordsToIndex( i, j, width ) ].type == type )
            ++count;

   return count;
}

std::vector<std::vector<int>> MapGenerator::getAndPruneLandBlobs( std::vector<Tile>& map ) const
{
   std::vector<std::vector<int>> blobs;
   blobs.reserve( continents * 8 );
   const int offsets[ 4 ] = { -1, +1, -width, +width };

   std::vector<std::uint8_t> visited( map.size(), 0 );
   std::queue<int> q;

   for( int start = 0; start < map.size(); ++start )
   {
      if( visited[ start ] )
         continue;

      if( map[ start ].type != TileType::Land )
      {
         visited[ start ] = 1;
         continue;
      }

      // New component (blob)
      // BFS
      std::vector<int> blob;
      q.push( start );
      visited[ start ] = 1;

      while( !q.empty() )
      {
         const int idx = q.front();
         q.pop();
         blob.push_back( idx );

         for( const int offset: offsets )
         {
            int neighbor = idx + offset;
            // The check can probably be done with only the neighbor. This is just to be safe
            auto coords = Math::indexToCoords( neighbor, width );

            if( coords.x < 0 || coords.x >= height || coords.y < 0 || coords.y >= width )
               continue;

            if( visited[ neighbor ] )
               continue;

            visited[ neighbor ] = 1;

            if( map[ neighbor ].type == TileType::Land )
               q.push( neighbor );
         }
      }

      // Keep only land components and optionally prune tiny islands
      if( blob.size() >= minBlobSize )
         blobs.push_back( std::move( blob ) );
      else
         for( const auto& idx: blob )
            map[ idx ].type = TileType::Water;
   }

   return blobs;
}

void MapGenerator::mergeSmallRegions( std::vector<Tile>& map, std::vector<Region>& regions ) const
{
   for( auto& region: regions )
   {
      if( region.tiles.size() < minRegionSize )
      {
         auto smallestNeighbor = getSmallestRegionNeighbor( map, regions, region.id );

         for( auto tile: region.tiles )
         {
            map[ tile ].regionId = smallestNeighbor;
            regions[ smallestNeighbor - 1 ].tiles.push_back( tile );
         }

         region.tiles.clear();
         region.invalid = true;
      }
   }
}

unsigned int MapGenerator::getSmallestRegionNeighbor( const std::vector<Tile>& map, const std::vector<Region>& regions,
                                                      unsigned int regionIndex ) const
{
   unsigned int smallestNeighbor = 0;
   size_t smallestVolume = std::numeric_limits<size_t>::max();
   const int offsets[ 4 ] = { -1, +1, -width, +width };

   for( auto tile: regions[ regionIndex - 1 ].tiles )
   {
      for( auto offset: offsets )
      {
         int neighbor = tile + offset;
         if( neighbor < 0 || neighbor >= map.size() )
            continue;

         // Check for a different region and if the region is smaller than the smallest one yet
         if( map[ neighbor ].regionId != regionIndex && map[ neighbor ].regionId != 0 &&
             regions[ map[ neighbor ].regionId - 1 ].tiles.size() < smallestVolume )
         {
            smallestNeighbor = map[ neighbor ].regionId;
            smallestVolume = regions[ map[ neighbor ].regionId - 1 ].tiles.size();
         }
      }
   }

   return smallestNeighbor;
}

std::vector<int> MapGenerator::samplePointsAndRegions( std::vector<int>& blob, int amount, std::mt19937& rng )
{
   std::vector<int> samples;
   samples.reserve( amount );
   std::ranges::shuffle( blob, rng );

   for( int i = 0; i < blob.size() && samples.size() <= amount; ++i )
   {
      bool tooClose = false;
      auto coords = Math::indexToCoords( blob[ i ], width );

      for( const auto& sample: samples )
      {
         auto sampleCoords = Math::indexToCoords( sample, width );

         if( std::hypot( coords.x - sampleCoords.x, coords.y - sampleCoords.y ) <= minSeedDistance )
         {
            tooClose = true;
            break;
         }
      }

      if( !tooClose )
         samples.push_back( blob[ i ] );
   }

   return samples;
}
