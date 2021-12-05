#include <physica/entity.h>
#include <physica/line.h>
#include <physica/macros.h>
#include <physica/ray.h>
#include <string.h>

unsigned int ph_entity_vs_ray(PHEntity *entity, PHRay ray) {
  PHAABB a = ph_entity_aabb(entity);

  float x1 = ray.start.x;
  float x2 = ray.end.x;
  float y1 = ray.start.y;
  float y2 = ray.end.y;

  float rx = a.min.x;
  float ry = a.min.y;
  float rw = entity->size.x;
  float rh = entity->size.y;

  unsigned int left = ph_line_intersects(x1, y1, x2, y2, rx, ry, rx, ry + rh);
  unsigned int right =
      ph_line_intersects(x1, y1, x2, y2, rx + rw, ry, rx + rw, ry + rh);
  unsigned int top = ph_line_intersects(x1, y1, x2, y2, rx, ry, rx + rw, ry);
  unsigned int bottom =
      ph_line_intersects(x1, y1, x2, y2, rx, ry + rh, rx + rw, ry + rh);

  return (left || right || top || bottom);
}

PHRaycastResult *ph_init_raycast_result(void *ptr, PHRay ray) {
  PHRaycastResult *result = NEW(PHRaycastResult);
  result->ptr = ptr;
  result->ray = NEW(PHRay);
  memcpy(&result->ray->center, &ray.center, sizeof(ray.center));
  memcpy(&result->ray->direction, &ray.direction, sizeof(ray.direction));
  memcpy(&result->ray->start, &ray.start, sizeof(ray.start));
  memcpy(&result->ray->end, &ray.end, sizeof(ray.end));
  result->ray->distance = ray.distance;
  return result;
}

PHRaycastResult *ph_raycast(PHEntity **entities, uint32_t len, PHEntity *self,
                            PHRay ray) {
  for (uint32_t i = 0; i < len; i++) {
    PHEntity *entity = (PHEntity *)entities[i];
    if (entity == self)
      continue;
    if (ph_entity_vs_ray(entity, ray))
      return ph_init_raycast_result(entity, ray);
  }

  return 0;
}
