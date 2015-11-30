#include <cmath>
#include "Vec3.h"

Vec3 vec::make(float x, float y, float z) {
  Vec3 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

Vec3 vec::add(Vec3 a, Vec3 b) {
  Vec3 c;
  c.x = a.x + b.x;
  c.y = a.y + b.y;
  c.z = a.z + b.z;
  return c;
}

Vec3 vec::sub(Vec3 a, Vec3 b) {
  Vec3 c;
  c.x = a.x - b.x;
  c.y = a.y - b.y;
  c.z = a.z - b.z;
  return c;
}

float vec::mag_sq(Vec3 v) {
  return pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
}

float vec::mag(Vec3 v) {
  return sqrt(vec::mag_sq(v));
}

float vec::dot(Vec3 a, Vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec::norm(Vec3 v) {
  float mag = vec::mag(v);
  Vec3 normed;
  normed.x = v.x / mag;
  normed.y = v.y / mag;
  normed.z = v.z / mag;
  return normed;
}

std::string vec::to_string(Vec3 v) {
  return "<Vec3 x=" + std::to_string(v.x) + " y=" + std::to_string(v.y) + " z=" + std::to_string(v.z) + ">";
}
