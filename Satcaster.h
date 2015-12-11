#ifndef SATCASTER_H
#define SATCASTER_H

#include <cmath>
#include <string>
#include "Buffer.h"
#include "Camera.h"
#include "Sphere.h"
#include "Vec3.h"
#include "Scene.h"

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
  Buffer* render(const Scene& scene);
private:
  Intersection* get_intersection(const Ray &ray, const Sphere &sphere);
  float get_intersection_distance(const Ray &ray, const Sphere &sphere);
  Buffer* dither(const Buffer &rawBuffer);
};


#endif
