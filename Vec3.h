#ifndef VEC3_H
#define VEC3_H

#include <string>

class Vec3 {
public:
  float x;
  float y;
  float z;

  Vec3 ();
  Vec3 (float x, float y, float z);

  Vec3 operator+(const Vec3 &other) const;
  Vec3 operator-(const Vec3 &other) const;
  Vec3 operator*(float scalar) const;
  Vec3 norm();

  float mag_sq();
  float mag();

  float dot(const Vec3 &other);

  std::string to_string();
};

#endif

