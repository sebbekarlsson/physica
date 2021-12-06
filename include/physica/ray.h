#ifndef PHYSICA_RAY_H
#define PHYSICA_RAY_H
#include <vec/vec.h>
#include <stdint.h>

struct PHYSICA_ENTITY_STRUCT;

#define PH_ENTITY struct PHYSICA_ENTITY_STRUCT

typedef struct PH_RAY_STRUCT {
  Vec3 start;
  Vec3 end;
  Vec3 center;
  Vec3 direction;
  float distance;
  unsigned int hit;
  int cooldown;
} PHRay;

typedef struct PH_RAYCAST_RESULT_STRUCT {
  PHRay* ray;
  void *ptr;
  PH_ENTITY* entity;
} PHRaycastResult;


unsigned int ph_entity_vs_ray(PH_ENTITY* actor, PHRay ray);

PHRaycastResult* ph_init_raycast_result(void* ptr, PHRay ray, PH_ENTITY* entity);

PHRaycastResult* ph_raycast(PH_ENTITY** entities, uint32_t len, PH_ENTITY* self, PHRay ray);
#endif
