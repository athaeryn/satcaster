#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"

struct Camera {
  Vec3 pos;
  Vec3 dir;

  Camera(Vec3 position, Vec3 direction) {
    pos = position;
    dir = direction;
  }
};

#endif
