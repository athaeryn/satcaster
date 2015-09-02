#ifndef SATCASTER_H
#define SATCASTER_H

#include <vector>
#include "Camera.h"
#include "Sphere.h"
#include "Vec3.h"

using namespace std;
using namespace vec;


class Satcaster {
public:
  Satcaster();
  Camera camera;
  void render(int buffer[], int w, int h);
private:
  vector<Sphere> spheres;
  bool does_intersect(Vec3 start, Vec3 dir, Sphere sphere);
};


#endif
