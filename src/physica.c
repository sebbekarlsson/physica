#include <physica/physica.h>
#include <vec/vec.h>
#include <stdio.h>

void ph_next(PHEntity *a) {
  if (!a->mass) a->mass = ph_entity_compute_mass(a);

  if (!a->can_be_moved)
    return;

  a->position.x += a->delta_position.x;
  a->position.y += a->delta_position.y;

  *a = *a;
}
