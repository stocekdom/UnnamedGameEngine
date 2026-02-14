#include "UUID.h"

std::mt19937_64 UUID::s_engine(
   static_cast<uint64_t>( std::chrono::high_resolution_clock::now().time_since_epoch().count() )
);

std::uniform_int_distribution<uint64_t> UUID::s_dist;

UUID::UUID() : id( generateId() )
{
}

//
// Created by dominik on 02.12.25.
//
UUID::UUID( uint64_t newId ) : id( newId )
{
}

uint64_t UUID::value() const
{
   return id;
}

bool UUID::operator<( const UUID& other ) const
{
   return id < other.id;
}

bool UUID::operator==( const UUID& other ) const
{
   return id == other.id;
}

bool UUID::operator!=( const UUID& other ) const
{
   return id != other.id;
}

uint64_t UUID::generateId()
{
   return s_dist( s_engine );
}
