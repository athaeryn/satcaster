#ifndef SATCASTER_H
#define SATCASTER_H

#include <cmath>
#include <string>
#include <vector>
#include "Buffer.h"
#include "Camera.h"
#include "Sphere.h"
#include "Vec3.h"

using namespace std;

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
  void add_body(Sphere &s);
  void render(Buffer &buffer);
private:
  vector<Sphere> spheres;
  void dither(const Buffer &rawBuffer, Buffer &output);
  bool get_intersection(Intersection &intersection, const Ray ray, const Sphere sphere);
  float get_intersection_distance(const Ray &ray, const Sphere &sphere);
  /* void dither(int buffer[], Ditherer ditherer); */
};


#endif
