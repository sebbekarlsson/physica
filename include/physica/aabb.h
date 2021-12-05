#ifndef PHYSICA_AABB_H
#define PHYSICA_AABB_H
#include <vec/vec.h>
typedef struct PH_AABB_STRUCT {
 Vec3 min;
 Vec3 max;
} PHAABB;

unsigned int ph_AABB_intersects(PHAABB a, PHAABB b);
#endif
