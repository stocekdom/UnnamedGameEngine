//
// Created by dominik on 07.02.26.
//

#include "MapGenerator.h"
#include "../Core/Math.h"

// Setting distributions like this is slower and wasteful.
// If performance is an issue> https://martin.ankerl.com/2018/12/08/fast-random-bool/
MapGenerator::MapGenerator( size_t seed ) : rng( seed ), floatDist( 0, 1 ), bitDistribution( 0, 1 ), width( 0 ), height( 0 )
{
}

std::vector<Tile> MapGenerator::generateMap( int mapWidth, int mapHeight )
{
   std::vector<Tile> map( mapWidth * mapHeight );
   width = mapWidth;
   height = mapHeight;

   auto chunks = generateMapChunks();

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

std::vector<Region> MapGenerator::generateRegions( std::vector<Tile>& map, int mapWidth, int mapHeight )
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
      auto samples = samplePointsAndRegions( blob, std::ceil( blob.size() / ( minRegionSize * 4 ) ) );

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
         const int x = neighbor / width; // row
         const int y = neighbor % width; // col

         if( x < 0 || x >= height || y < 0 || y >= width )
            continue;

         if( map[ neighbor ].regionId == 0 && map[ neighbor ].type == TileType::Land )
         {
            map[ neighbor ].regionId = map[ idx ].regionId;
            regions[ map[ idx ].regionId - 1 ].tiles.push_back( neighbor );
            tilesToProcess.push( neighbor );
         }
      }
   }

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

std::vector<MapGenerator::Chunk> MapGenerator::generateMapChunks()
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

bool MapGenerator::shouldVerticalSplit( const Chunk& chunk )
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
