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
  float t;
};

struct Ray {
  Vec3 origin;
  Vec3 dir;
};


class Satcaster {
public:
  Camera camera;
  Vec3 light;
  void add_body(float x, float y, float z, float r, string seed);
  void render(int buffer[], int w, int h);
private:
  vector<Sphere> spheres;
  bool get_intersection(Intersection &intersection, const Ray ray, const Sphere sphere);
  float get_intersection_distance(const Ray &ray, const Sphere &sphere);
};


#endif
