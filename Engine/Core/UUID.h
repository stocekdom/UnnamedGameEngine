//
// Created by dominik on 02.12.25.
//

#ifndef GAME1_UUID_H
#define GAME1_UUID_H

#include <random>
#include <chrono>

class UUID
{
   public:
      UUID();

      explicit UUID( uint64_t newId );

      [[nodiscard]] uint64_t value() const;

      bool operator<( const UUID& other ) const;

      bool operator==( const UUID& other ) const;

      bool operator!=( const UUID& other ) const;

   private:
      uint64_t id;

      // Random number engine and distribution.
      static std::mt19937_64 s_engine;
      static std::uniform_int_distribution<uint64_t> s_dist;

      static uint64_t generateId();
};

// Std hash template specialization.
template<>
struct std::hash<UUID>
{
   size_t operator()( const UUID& id ) const noexcept
   {
      return std::hash<uint64_t>{}( id.value() );
   }
};
#endif //GAME1_UUID_H
