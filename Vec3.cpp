#include <cmath>
#include "Vec3.h"

Vec3::Vec3 () {
  x = 0;
  y = 0;
  z = 0;
}

Vec3::Vec3 (float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}

Vec3 Vec3::operator+ (const Vec3 &other) const {
  Vec3 result (
    x + other.x,
    y + other.y,
    z + other.z
  );
  return result;
}

Vec3 Vec3::operator- (const Vec3 &other) const{
  Vec3 result (
    x - other.x,
    y - other.y,
    z - other.z
  );
  return result;
}

Vec3 Vec3::operator* (float scalar) const {
  Vec3 result (
    x * scalar,
    y * scalar,
    z * scalar
  );
  return result;
}

float Vec3::mag_sq() {
  return pow(x, 2) + pow(y, 2) + pow(z, 2);
}

float Vec3::mag() {
  return sqrt(mag_sq());
}

float Vec3::dot(const Vec3 &other) {
  return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::norm() {
  float _mag = mag();
  Vec3 normed (x / _mag, y / _mag, z / _mag);
  return normed;
}

std::string Vec3::to_string() {
  return "<Vec3 x=" + std::to_string(x) + " y=" + std::to_string(y) + " z=" + std::to_string(z) + ">";
}
