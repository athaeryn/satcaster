#ifndef SCENE_H
#define SCENE_H

#include <vector>

struct Scene {
  Camera camera;
  Vec3 light;
  std::vector<Sphere> spheres;
  int height;
  int width;
};

#endif
