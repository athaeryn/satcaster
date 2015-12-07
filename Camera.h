#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"

struct Camera {
  Vec3 pos;
  Vec3 dir;
  float fov;

  Camera() {
    pos = Vec3(0, 0, 0);
    dir = Vec3(0, 0, -1);
    fov = 90;
  }

  Camera(Vec3 position, Vec3 direction, float field_of_view) {
    pos = position;
    dir = direction;
    fov = field_of_view;
  }
};

#endif
