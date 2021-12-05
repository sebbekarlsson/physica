#include <physica/entity.h>
#include <math.h>


PHAABB ph_entity_aabb(PHEntity* a) {
  PHAABB aabb3d = {};

  float a_height = a->size.y;
  float a_width = a->size.x;

  aabb3d.min.x = a->position.x - a->delta_position.x;
  aabb3d.max.x = a->position.x + a->delta_position.x + a_width;
  aabb3d.min.y = a->position.y - a->delta_position.y;
  aabb3d.max.y = a->position.y + a->delta_position.y + a_height;

  return aabb3d;
}

unsigned int ph_entity_intersects(PHEntity* a, PHEntity *b) {
  PHAABB x = ph_entity_aabb(a);
  PHAABB y = ph_entity_aabb(b);

  return ph_AABB_intersects(x, y);
}


float ph_entity_compute_mass(PHEntity* a) {
  return fmax(fmax(a->size.x, a->size.y), a->size.z);
}


void ph_entity_apply_force(PHEntity* a, Vec3 force) {
  vec3_copy(VEC3_OP(a->delta_position, +, force), &a->delta_position);
}
