#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"

struct Sphere {
  Vec3 pos;
  float r;

  Sphere(Vec3 position, float radius) {
    pos = position;
    r = radius;
  }
};

#endif
