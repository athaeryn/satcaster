#ifndef __SC_SPHERE_HEADER_INCLUDE__
#define __SC_SPHERE_HEADER_INCLUDE__

#include <Eigen/Dense>

using namespace std;
using Eigen::Vector3f;

class Sphere {
public:
  Sphere(Vector3f center, float radius);
  string to_string();
private:
  Vector3f pos;
  float r;
};

#endif
