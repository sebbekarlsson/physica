#include <math.h>
#include <physica/physica.h>
#include <physica/system.h>
#include <physica/delay.h>
#include <stdio.h>

#define THIS system

#define SET_LAST_UPDATE()                                                      \
  {                                                                            \
    Date last_update = date_now();                                             \
    date_copy(&THIS->last_update, &last_update);                               \
  }

void ph_system_set_entities_ptr(PHSystem *system, PHEntity **entities,
                                uint32_t *length) {
  system->entities = entities;
  system->length = length;
}

static void *loop(void *ptr) {
  printf("Physica System: Entered main loop.\n");
  PHSystem *system = (PHSystem *)ptr;

  while (system->running) {
    ph_system_update(system);
  }

  printf("Physica System: main loop done.\n");

  pthread_exit(0);
}

void ph_system_start(PHSystem *system) {
  if (system->running)
    return;

  printf("Physica System: starting system...\n");

  if (pthread_mutex_init(&system->lock, 0)) {
    printf("Physica system: Could not create mutext.\n");
    return;
  }

  if (pthread_create(&system->thread_id, 0, loop, system)) {
    printf("Physica system: Failed to create thread.\n");
    return;
  }

  system->running = 1;

  printf("Physica System: System running.\n");
}

void ph_system_stop(PHSystem *system) {
  system->running = 0;
  pthread_join(system->thread_id, 0);
}

void ph_system_update(PHSystem *system) {

  pthread_mutex_lock(&system->lock);
    Date now = date_now();
  Date elapsed = date_diff(&now, &THIS->created_at);
  double elapsed_time = elapsed.milliseconds_static;
  double dt = (elapsed_time - THIS->old_t) / 1000.0f;

  THIS->old_t = elapsed_time;
  THIS->delta = dt;


  uint32_t length = *system->length;
  for (uint32_t i = 0; i < length; i++) {
    PHEntity *entity = system->entities[i];

    unsigned int ray_hit = 0;

      PHRay ray = {};
      ray.start = vec3_center(entity->position, entity->size);
      float half = entity->size.x / 2;
      Vec3 delta = entity->delta_position;
      float a = vec3_angle_between(VEC3_OP(ray.start, +, delta), ray.start);
      int aa = ((int)a) % 360;
      if (aa < 0)
        aa += 360;
      a = (float)aa;
      float r = a / 180 * M_PI;
      ray.start.x += cos(r) * (half + entity->inv_mass);
      ray.start.y += sin(r) * (half + entity->inv_mass);
      ray.end =
          VEC3_OP(ray.start, +, VEC3_OP_SR(entity->delta_position, *, 1.5f));
      ray.start.z = 3.0f;
      ray.end.z = 3.0f;

      PHRaycastResult *result = 0;
      if ((result = ph_raycast(system->entities, length, entity, ray))) {

        if (result->entity) {
          ph_resolve_collision(entity, result->entity);
          ray_hit = 1;
        }
        if (system->callback) {
          system->callback((PHSystemCollision){COLLISION_RAY, ray, result,
                                               entity, result->entity});
        }
      }


    if (!ray_hit) {
      for (uint32_t j = 0; j < length; j++) {
        PHEntity *other = system->entities[j];
        if (other == entity)
          continue;

        if (ph_entity_intersects(entity, other)) {
            ph_resolve_collision(entity, other);
          if (system->callback) {
            system->callback((PHSystemCollision){COLLISION_INTERSECT, (PHRay){},
                                                0, entity, other});
          }
        }
      }
    }

    ph_next(entity);
  }

    SET_LAST_UPDATE();

  Date nownow = date_now();
  Date diff = date_diff(&nownow, &THIS->start_time);


  ph_delay(floorf(16.666f - diff.milliseconds_static));


  if (diff.timestamp >= 1) {
    THIS->fps = THIS->frames;
    THIS->frames = 0;
    date_copy(&THIS->start_time, &nownow);
  } else {
    THIS->frames += 1;
  }

  pthread_mutex_unlock(&system->lock);
}
