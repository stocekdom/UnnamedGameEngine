//
// Created by dominik on 21.12.25.
//

#ifndef GAME1_UTILITY_H
#define GAME1_UTILITY_H
#include <vector>

namespace Utility
{
   /**
    * Performs a swap and pop technique on a vector to remove a matching element in O(1)
    * @param v The vector on which the operation is performed
    * @param element The element to be deleted
    * @return Returns the result flag of the operation. False - element not found; true - element deleted
    * @note Uses std::ranges::find which means only the first found element is popped
    */
   template<typename T>
   bool vectorSwapAndPop( std::vector<T>& v, const T& element )
   {
      auto it = std::ranges::find( v, element );
      if( it != v.end() )
      {
         std::swap( *it, v.back() );
         v.pop_back();
         return true;
      }

      return false;
   }
}

#endif //GAME1_UTILITY_H
