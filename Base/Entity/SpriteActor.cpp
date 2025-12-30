//
// Created by dominik on 23.12.25.
//

#include "SpriteActor.h"

#include "../Sprite/SpriteComponent.h"

SpriteActor::SpriteActor( Entity id, GameScene* scene, const std::string& texturePath, const ActorParams& params,
                          SpriteMobility mobility )
   : Actor( id, scene, params )
{
   scene->addComponent<SpriteComponent>( id, texturePath, mobility );
}
