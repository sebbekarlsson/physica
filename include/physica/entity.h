#ifndef PHYSICA_ENTITY_H
#define PHYSICA_ENTITY_H
#include <physica/aabb.h>

typedef struct PHYSICA_ENTITY_STRUCT {
  Vec3 position;
  Vec3 delta_position;
  Vec3 size;
  Vec3 velocity;
  float restitution;
  float mass;
  float inv_mass;
  unsigned int hard;
  unsigned int can_be_moved;
} PHEntity;

PHAABB ph_entity_aabb(PHEntity* a);

unsigned int ph_entity_intersects(PHEntity* a, PHEntity *b);

float ph_entity_compute_mass(PHEntity* a);

void ph_entity_apply_force(PHEntity* a, Vec3 force);
#endif
