#ifndef SATCASTER_H
#define SATCASTER_H

#include <cmath>
#include <vector>
#include "Camera.h"
#include "Sphere.h"
#include "Vec3.h"

using namespace std;
using namespace vec;


class Satcaster {
public:
  Camera camera;
  void add_body(float x, float y, float z, float r);
  void render(int buffer[], int w, int h);
private:
  vector<Sphere> spheres;
  bool does_intersect(Vec3 start, Vec3 dir, Sphere sphere);
};


#endif