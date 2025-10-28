//
// Created by dominik on 09.10.25.
//
#include "BowCommands.h"

static constexpr float ROTATION_SPEED = 30.0f;

RotateUp::RotateUp( const std::shared_ptr<Bow>& bow ) : pawn( bow )
{
}

void RotateUp::execute()
{
   if( auto p = pawn.lock() )
      p->rotate( -ROTATION_SPEED );
}

void RotateUp::stop()
{
   if( auto p = pawn.lock() )
      p->rotate( 0 );
}

RotateDown::RotateDown( const std::shared_ptr<Bow>& bow ) : pawn( bow )
{
}

void RotateDown::execute()
{
   if( auto p = pawn.lock() )
      p->rotate( ROTATION_SPEED );
}

void RotateDown::stop()
{
   if( auto p = pawn.lock() )
      p->rotate( 0 );
}

Charging::Charging( const std::shared_ptr<Bow>& bow ) : pawn( bow )
{
}

void Charging::execute()
{
   if( auto p = pawn.lock() )
      p->charge( 20 );
}

void Charging::stop()
{
   if( auto p = pawn.lock() )
      p->fire();
}
