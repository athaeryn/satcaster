#ifndef __SC_SPHERE_HEADER_INCLUDE__
#define __SC_SPHERE_HEADER_INCLUDE__

#include <Eigen/Dense>

using namespace std;
using Eigen::Vector3f;

class Sphere {
public:
  Sphere(float x, float y, float z);
  string get_position_string();
private:
  Vector3f center;
};

#endif
