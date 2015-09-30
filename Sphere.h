#ifndef SPHERE_H
#define SPHERE_H

#include <string>
#include "Vec3.h"

struct Sphere {
  Vec3 pos;
  float r;
  std::string seed;

  Sphere(Vec3 position, float radius, std::string randomSeed) {
    pos = position;
    r = radius;
    seed = randomSeed;
  }
};

#endif
