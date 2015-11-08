#ifndef SATCASTER_H
#define SATCASTER_H

#include <cmath>
#include <string>
#include <vector>
#include "Camera.h"
#include "Sphere.h"
#include "Vec3.h"

using namespace std;
using namespace vec;


struct Intersection {
  Vec3 pos;
  Vec3 normal;
};


class Satcaster {
public:
  Camera camera;
  void add_body(float x, float y, float z, float r, string seed);
  void render(int buffer[], int w, int h);
private:
  vector<Sphere> spheres;
  Intersection* get_intersection(Vec3 start, Vec3 dir, Sphere sphere);
};


#endif
