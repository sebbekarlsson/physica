#ifndef PHYSICA_LINE_H
#define PHYSICA_LINE_H
#include <vec/vec.h>
Vec3 vec3_center_of_line(Vec3 start, Vec3 end);
unsigned int ph_line_intersects(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
#endif
