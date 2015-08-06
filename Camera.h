#ifndef __SC_CAMERA_HEADER_INCLUDE__
#define __SC_CAMERA_HEADER_INCLUDE__

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using Eigen::Vector3f;

class Camera {
public:
  Camera(Vector3f center);
  string to_string();
  void lookAt(const Vector3f *point);
private:
  Vector3f pos;
  Vector3f lookTarget;
};

#endif
