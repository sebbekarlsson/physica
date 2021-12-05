#include <physica/collision.h>
#include <physica/macros.h>
#include <math.h>


static PHCollision _resolve_collision(PHEntity *a, PHEntity *b, Vec3 zero, Vec3 dp,
                             Vec3 dpb) {
  // Vec3 dp = vec3_zero(a->delta_position, zero);
  // Vec3 dpb = vec3_zero(b->delta_position, zero);
  //Vec3 bpos = vec3_zero(b->position, zero);
  Vec3 rv = vec3_uninf(vec3_sub(dp, dpb));
  Vec3 normal = ph_vec3_impulse_normal(
      (PHEntity){a->position, dp, (Vec3){a->mass, a->mass, a->mass}},
      (PHEntity){b->position, dpb, (Vec3){b->size.x, b->mass, b->size.z}});

  float alongNormal = vec3_dot(rv, normal);

  if (alongNormal > 0)
    return (PHCollision){0, 0, normal};

  alongNormal = alongNormal;

  float j = alongNormal;

  Vec3 impulse = VEC3_OP_SL(j, *, normal);

  float mass_sum = a->mass + b->mass;

  float a_ratio = 0;

  {
    a_ratio = ceilf(ONE(a->mass / mass_sum));
    Vec3 next_delta =
        VEC3_OP(a->delta_position, -, VEC3_OP_SL(a_ratio, *, impulse));
    vec3_copy(next_delta, &a->delta_position);
  }

  if (b->can_be_moved) {
    float ratio = ceilf(ONE(b->mass / mass_sum));
    Vec3 next_delta =
        VEC3_OP(b->delta_position, +, VEC3_OP_SL(ratio, *, impulse));
    vec3_copy(next_delta, &b->delta_position);
  }

  return (PHCollision){1, a_ratio, normal};
}

void ph_resolve_collision(PHEntity *a, PHEntity *b) {
  if (!a->can_be_moved)
    return;

  PHCollision ca;
  PHCollision cb;

  Vec3 zero_x = (Vec3){0, 1, 0};
  Vec3 zero_y = (Vec3){1, 0, 0};
  Vec3 a_delta = a->delta_position;
  Vec3 b_delta = b->delta_position;
  if (floorf(a->delta_position.y) != 0)
    cb = _resolve_collision(a, b, zero_x, vec3_zero(a_delta, zero_x),
                            vec3_zero(b_delta, zero_x));

  if (floorf(a->delta_position.x) != 0)
    ca = _resolve_collision(a, b, zero_y, vec3_zero(a_delta, zero_y),
                            vec3_zero(b_delta, zero_y));

  if (ca.collision == 0 && cb.collision == 0)
    return;

  if (!ph_entity_intersects(a, b))
    return;

  Vec3 normal = cb.normal; // VEC3_OP(ca.normal, + , cb.normal);

  // physics_next(b);

  // correct position
  Vec3 penetration =
      vec3_mul((VEC3_OP(VEC3_OP(a->position, +, a->delta_position), -,
                            VEC3_OP_SR(b->position, +, b->mass))),
                   vec3_inv(normal));
  const float percent = cb.ratio;

  float slop = 0.01f;
  Vec3 correct = VEC3_OP(
      VEC3_OP_SR((VEC3_OP_SR(vec3_max(VEC3_OP_SR(penetration, -, slop), 0),
                             /, (ONE(a->inv_mass + b->inv_mass)))),
                     *, percent),
          *, normal);

  vec3_copy(VEC3_OP(a->position, +, VEC3_OP_SL(a->inv_mass, *, correct)),
                &a->position);

}


#include <stdio.h>
// get normal vector of the object `b` which `a` is traveling towards.
// to figure out which side of `b` which `a` will hit.
Vec3 ph_vec3_impulse_normal(PHEntity a, PHEntity b) {
  Vec3 a_pos = VEC3_OP(a.position, +, a.delta_position);
  Vec3 b_pos = VEC3_OP(b.position, +, b.delta_position);

  Vec3 center_a =  vec3_center(a_pos, a.size);// (Vec3){ a_pos.x + a.size.x / 2, a_pos.y + a.size.y / 2, 0 };
  Vec3 center_b = vec3_center(b_pos, b.size);//(Vec3){ b_pos.x + b.size.x / 2, b_pos.y + b.size.y / 2, 0 };

  Vec3 x1 = {0, 0, 0};
  Vec3 y1 = {0, 0, 0};

  float left = a.position.x;
  float right = a.position.x + a.size.x;

  float b_right = b.position.x + b.size.x;
  float b_left = b.position.x;

  if (center_a.x > center_b.x && a.delta_position.x < 0 && left >= floorf(b_right)) x1 = (Vec3){1, 0, 0};
  else if (center_a.x < center_b.x && a.delta_position.x > 0 && floorf(right) <= b_left) x1 = (Vec3){-1, 0, 0};


  if ( center_a.y > center_b.y && a.delta_position.y < 0) y1 = (Vec3){0, 1, 0};
  else if ( center_a.y < center_b.y && a.delta_position.y > 0) y1 = (Vec3){0, -1, 0};

  Vec3 r = VEC3_OP(x1, +, y1);;

  return r;
}
