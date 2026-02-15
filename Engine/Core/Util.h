//
// Created by dominik on 21.12.25.
//

#ifndef GAME1_UTILITY_H
#define GAME1_UTILITY_H
#include <variant>
#include <vector>

namespace Util
{
   template<typename T, typename Variant>
   struct does_variant_contain;

   template<typename T, typename... Ts>
   struct does_variant_contain<T, std::variant<Ts...>>
   {
      static constexpr bool value = std::disjunction_v<std::is_same<T, Ts>...>;
   };

   template<typename T, typename Variant>
   concept does_variant_contain_v = does_variant_contain<T, Variant>::value;

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

   template<typename T>
   concept IsEnum = std::is_enum_v<T>;

   template<IsEnum E>
   constexpr auto enumToIndex( E e ) noexcept
   {
      return static_cast<std::underlying_type_t<E>>( e );
   }
}

#endif //GAME1_UTILITY_H
