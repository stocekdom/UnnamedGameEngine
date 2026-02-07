//
// Created by dominik on 07.02.26.
//

#include "MapGenerator.h"
#include <queue>

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
         for( int y = chunk.left + waterEdge; y < chunk.left + chunk.width - waterEdge ; ++y )
         {
            if( x < chunk.top + waterEdge + sparseLands || x >= chunk.top + chunk.height - waterEdge - sparseLands ||
                y < chunk.left + waterEdge + sparseLands || y >= chunk.left + chunk.width - waterEdge - sparseLands )
               map[ x + y * width ] = floatDist( rng ) <= edgeLandProbability ? Tile::Land : Tile::Water;
            else
               map[ x + y * width ] = floatDist( rng ) <= landProbability ? Tile::Land : Tile::Water;
         }

   cellularAutomataSmoothing( map, chunks );
   return map;
}

void MapGenerator::cellularAutomataSmoothing( std::vector<Tile>& map, const std::vector<Chunk>& chunks ) const
{
   for( const auto& chunk: chunks )
      for( int i = 0; i < automataIterations; ++i )
         cellularAutomateImpl( map, chunk );
}

void MapGenerator::cellularAutomateImpl( std::vector<Tile>& map, const Chunk& chunk ) const
{
   for( int x = chunk.top; x < chunk.top + chunk.height; ++x )
   {
      for( int y = chunk.left; y < chunk.left + chunk.width; ++y )
      {
         switch( map[ x + y * width ] )
         {
            case Tile::Water:
            {
               auto landNeighbors = countNeighborsOfType( map, chunk, x, y, Tile::Land );
               if( landNeighbors > maxLandNeighbors )
                  map[ x + y * width ] = Tile::Land;

               break;
            }
            case Tile::Land:
            {
               auto waterNeighbors = countNeighborsOfType( map, chunk, x, y, Tile::Water );
               if( waterNeighbors > maxWaterNeighbors )
                  map[ x + y * width ] = Tile::Water;

               break;
            }
         }
      }
   }
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

int MapGenerator::countNeighborsOfType( const std::vector<Tile>& map, const Chunk& chunk, int x, int y, Tile type ) const
{
   int count = 0;

   // X is the row, Y is the column. !!! Different from screen coordinates
   // Limit the iteration constants to the chunk bounds
   for( int i = std::max( chunk.top, x - 1 ); i <= std::min( chunk.top + chunk.height - 1, x + 1 ); ++i )
      for( int j = std::max( chunk.left, y - 1 ); j <= std::min( chunk.left + chunk.width - 1, y + 1 ); ++j )
         if( ( i != x || j != y ) && map[ i + j * width ] == type )
            ++count;

   return count;
}
