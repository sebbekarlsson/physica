#ifndef PHYSICA_SYSTEM_H
#define PHYSICA_SYSTEM_H
#include <physica/entity.h>
#include <physica/ray.h>
#include <stdint.h>
#include <pthread.h>
#include <date/date.h>

typedef enum {
COLLISION_RAY,
COLLISION_INTERSECT
} PHSystemCollisionType;

typedef struct PHYSICA_SYSTEM_COLLISION {
  PHSystemCollisionType type;
  PHRay ray;
  PHRaycastResult* ray_result;
  PHEntity* a;
  PHEntity* b;
  float frame_cap;
} PHSystemCollision;

typedef void (*PHSystemCollisionCallback)(PHSystemCollision collision);

typedef struct PHYSICA_SYSTEM_STRUCT {
  PHEntity** entities;
  uint32_t* length;
  pthread_mutex_t lock;
  pthread_t thread_id;
  unsigned int running;
  PHSystemCollisionCallback callback;
  Date last_update;
  Date created_at;
  Date start_time;
  double old_t;
  double delta;
  int fps;
  long int frames;
} PHSystem;

void ph_system_start(PHSystem* system);

void ph_system_stop(PHSystem* system);

void ph_system_set_entities_ptr(PHSystem* system, PHEntity** entities, uint32_t* length);

void ph_system_update(PHSystem* system);
#endif
