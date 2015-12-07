#include <iostream>
#include "Satcaster.h"

#define FAR 1000

void Satcaster::add_body(float x, float y, float z, float r, string seed) {
  Sphere s(vec::make(x, y, z), r, seed);
  spheres.push_back(s);
}


void Satcaster::render(Buffer &buffer) {
  int w = buffer.w;
  int h = buffer.h;
  float aspect = w / h;
  float fov = tan(camera.fov / 2 * M_PI / 180);

  Buffer rawBuffer (w, h);

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      float nx = ((2 * (x + .5) / w) - 1) * aspect * fov;
      float ny = 1 - (2 * (y + .5) / h) * fov;
      Vec3 rayDirection = norm(add(add(vec::make(nx, ny, 0), camera.pos), camera.dir));

      Intersection nearestIntersection = { camera.pos, camera.dir, FAR };

      for (Sphere sphere : spheres) {
        Intersection intersection;
        Ray ray = { camera.pos, rayDirection };
        if (get_intersection(intersection, ray, sphere)) {
          if (intersection.t < nearestIntersection.t) {
            nearestIntersection = intersection;
          }
        }
      }

      if (nearestIntersection.t < FAR) {
        Vec3 lightDir = norm(sub(light, nearestIntersection.pos));
        bool seesTheLight = true;
        Ray ray = { nearestIntersection.pos, lightDir };
        for (Sphere s : spheres) {
          if (get_intersection_distance(ray, s) > -1) {
            seesTheLight = false;
          }
        }
        if (seesTheLight) {
          float angleToLight = dot(lightDir, nearestIntersection.normal);
          rawBuffer[y * w + x] = 255 * angleToLight;
        } else {
          rawBuffer[y * w + x] = 0;
        }
      } else {
        rawBuffer[y * w + x] = 0;
      }
    }
  }


  // TODO: move dithering to its own function(s)
  // eventually the dithering algorithm could be chosen with a command line flag

  int *errorBuffer = new int[(w + 1) * (h + 1)];
  for (int i = 0; i < w * h; i++) {
    errorBuffer[i] = 0;
  }

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      int index = y * w + x;
      /* buffer[index] = rawBuffer[index]; continue; */
      int raw = rawBuffer[index] + errorBuffer[index];
      int diffFromHigh = raw - 255;
      int diffFromLow = raw;
      int error;
      if (abs(diffFromHigh) < abs(diffFromLow)) {
        error = diffFromHigh;
        buffer[index] = 255;
      } else {
        error = diffFromLow;
        buffer[index] = 0;
      }
#if 1
      // Floyd-Steinberg
      float sixteenth = error / 16.0f;
      errorBuffer[index + 1] += (int) sixteenth * 7.0f;
      errorBuffer[index + w] += (int) sixteenth * 5.0f;
      errorBuffer[index + w - 1] += (int) sixteenth * 3.0f;
      errorBuffer[index + w + 1] += (int) sixteenth;
#elif 0
      // "False Floyd-Steinberg"
      float eighth = (int) error / 8.0f;
      errorBuffer[index + 1] += (int) eighth * 3;
      errorBuffer[index + w] += (int) eighth * 3;
      errorBuffer[index + w + 1] += (int) eighth * 2;
#else
      // Atkinson
      int eighth = (int) error / 8.0f;
      errorBuffer[index + 1] += eighth;
      errorBuffer[index + 2] += eighth;
      errorBuffer[index + w] += eighth;
      errorBuffer[index + w + 2] += eighth;
      errorBuffer[index + w - 2] += eighth;
      errorBuffer[index + w * 2] += eighth;
#endif
    }
  }
}


bool Satcaster::get_intersection(Intersection &intersection, const Ray ray, const Sphere sphere) {
  float t0 = get_intersection_distance(ray, sphere);
  if (t0 < 0) return false;

  Vec3 hit = add(ray.origin, mult(ray.dir, t0));
  Vec3 normal = norm(sub(hit, sphere.pos));

  intersection.pos = hit;
  intersection.normal = normal;
  intersection.t = t0;
  return true;
}


// TODO: better variable names and explanation of this.
// I'm using the geometric solution described here:
// http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
float Satcaster::get_intersection_distance(const Ray &ray, const Sphere &sphere) {
  float no_intersection = -1;

  Vec3 L = sub(sphere.pos, ray.origin);
  float tca = dot(L, ray.dir);
  if (tca < 0) return no_intersection;
  float d2 = dot(L, L) - tca * tca;
  if (d2 > sphere.r) return no_intersection;
  float thc = sqrt(sphere.r - d2);
  float t0 = tca - thc;
  float t1 = tca + thc;

  if (t0 > t1) {
    swap(t0, t1);
  }

  if (t0 >= 0) {
    return t0;
  }

  return no_intersection;
}
