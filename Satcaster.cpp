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

      bool intersects = false;
      for (Sphere s : spheres) {
        Intersection* intersection = get_intersection(camera.pos, ray, s);
        if (intersection) {
          intersects = true;
        }
      }
      buffer[y * w + x] = intersects ? 1 : 0;
    }
  }
}


Intersection* Satcaster::get_intersection(Vec3 start, Vec3 dir, Sphere sphere) {
  Vec3 displacement = sub(sphere.pos, start);
  float a = mag_sq(dir);
  float b = 2 * dot(dir, displacement);
  float c = mag_sq(displacement) - pow(sphere.r, 2);
  float radicand = b * b - 4 * a * c;

  if (radicand >= 0) {
    Intersection i;
    return &i;
  } else {
    return nullptr;
  }
}
