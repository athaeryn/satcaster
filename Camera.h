#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"

struct Camera {
  Vec3 pos;
  Vec3 dir;
  float fov;

  Camera(Vec3 position, Vec3 direction, float field_of_view) {
    pos = position;
    dir = direction;
    fov = field_of_view;
  }
};

#endif
