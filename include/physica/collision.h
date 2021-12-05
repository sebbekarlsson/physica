#ifndef PHYSICA_COLLISION_H
#define PHYSICA_COLLISION_H
#include <vec/vec.h>
#include <physica/entity.h>
typedef struct {
  unsigned int collision;
  float ratio;
  Vec3 normal;
} PHCollision;

Vec3 ph_vec3_impulse_normal(PHEntity a, PHEntity b);

void ph_resolve_collision(PHEntity *a, PHEntity *b);
#endif
