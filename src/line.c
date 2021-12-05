#include <physica/line.h>

Vec3 vec3_center_of_line(Vec3 start, Vec3 end) {
  float x = (start.x + end.x) / 2;
  float y = (start.y + end.y) / 2;
  float z = (start.z + end.z) / 2;

  return (Vec3){x, y, z};
}

unsigned int ph_line_intersects(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

  // calculate the distance to intersection point
  float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

  // if uA and uB are between 0-1, lines are colliding
  if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) { return 1; }

  return 0;
}

