#ifndef VEC3_H
#define VEC3_H

#include <string>

struct Vec3 {
  float x;
  float y;
  float z;
};

namespace vec {
  Vec3 make(float x, float y, float z);
  Vec3 add(Vec3 a, Vec3 b);
  Vec3 sub(Vec3 a, Vec3 b);
  Vec3 norm(Vec3 v);
  Vec3 mult(Vec3 v, float scalar);
  float mag_sq(Vec3 v);
  float mag(Vec3 v);
  float dot(Vec3 a, Vec3 b);

  std::string to_string(Vec3 v);
}

#endif

