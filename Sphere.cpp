#include "Sphere.h"

Sphere::Sphere(float x, float y, float z) {
  center = Vector3f(x, y, z);
}

string Sphere::get_position_string() {
  return "(X:" + to_string(center[0])
      +  " Y:" + to_string(center[1])
      +  " Z:" + to_string(center[2]) + ")";
}
