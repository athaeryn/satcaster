#include <iostream>
#include "Satcaster.h"


void Satcaster::add_body(float x, float y, float z, float r, string seed) {
  Sphere s(vec::make(x, y, z), r, seed);
  spheres.push_back(s);
}


void Satcaster::render(int buffer[], int w, int h) {
  float aspect = w / h;
  float fov = tan(camera.fov / 2 * M_PI / 180);
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      float nx = ((2 * (x + .5) / w) - 1) * aspect * fov;
      float ny = 1 - (2 * (y + .5) / h) * fov;
      Vec3 ray = norm(add(add(vec::make(nx, ny, 0), camera.pos), camera.dir));

      vector<Intersection> intersections;
      for (Sphere s : spheres) {
        Intersection intersection;
        if (get_intersection(intersection, camera.pos, ray, s)) {
          intersections.push_back(intersection);
        }
      }
      if (intersections.size() > 0) {
        Intersection i = intersections.at(0);
        float shade = vec::dot(ray, i.normal);
        float value = 255 * shade * -1;
        if (value > (rand() % 100 + 150)) {
          buffer[y * w + x] = 255;
        } else {
          buffer[y * w + x] = 0;
        }
      } else {
        buffer[y * w + x] = 0;
      }
    }
  }

  // DITHER! ...or maybe later.
}


bool Satcaster::get_intersection(Intersection &intersection, Vec3 start, Vec3 dir, Sphere sphere) {
  // TODO: better names and explanation of this.
  // I'm using the geometric solution described here:
  // http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

  Vec3 L = sub(sphere.pos, start);
  float tca = dot(L, dir);
  if (tca < 0) return false;
  float d2 = dot(L, L) - tca * tca;
  if (d2 > sphere.r) return false;
  float thc = sqrt(sphere.r - d2);
  float t0 = tca - thc;
  float t1 = tca + thc;

  if (t0 > t1) {
    swap(t0, t1);
  }

  if (t0 < 0) return false;

  Vec3 hit = add(start, mult(dir, t0));
  Vec3 normal = norm(sub(hit, sphere.pos));

  intersection.pos = hit;
  intersection.normal = normal;
  return true;
}
