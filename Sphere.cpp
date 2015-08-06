#include "Sphere.h"

Sphere::Sphere(Vector3f center, float radius) {
  pos = center;
  r = radius;
}

string Sphere::to_string() {
  return "<Sphere r:" + std::to_string(r)
      +  " pos:[" + std::to_string(pos[0])
      +  ", "     + std::to_string(pos[1])
      +  ", "     + std::to_string(pos[2]) + "]>";
}
