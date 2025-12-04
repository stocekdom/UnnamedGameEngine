//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_SPAWNCATEGORY_H
#define GAME1_SPAWNCATEGORY_H

/**
 * Defines how the entity should be spawned and how it's handled by the scene upon registering
 */
enum class SpawnCategory
{
   WORLD, // Entities that are part of the world and are rendered based on their depth. Rendered below overlays
   OVERLAY, // Entities that are drawn on top of everything else and act as overlays. They are not sorted by depth
};
#endif //GAME1_SPAWNCATEGORY_H
