#include <physica/aabb.h>

unsigned int ph_AABB_intersects(PHAABB a, PHAABB b) {
  if (a.max.x < b.min.x || a.min.x > b.max.x)
    return 0;
  if (a.max.y < b.min.y || a.min.y > b.max.y)
    return 0;
  if (a.max.y < b.min.z || a.min.z > b.max.z)
    return 0;
  return 1;
}
