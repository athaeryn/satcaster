#include "Camera.h"

Camera::Camera(float x, float y, float z) {
  center = Vector3f(x, y, z);
}

string Camera::get_position_string() {
  return "(X:" + to_string(center[0])
      +  " Y:" + to_string(center[1])
      +  " Z:" + to_string(center[2]) + ")";
}

void Camera::lookAt(const Vector3f *point) {
  cout << "camera looking at (" << (*point)[0] << ", " << (*point)[1] << ", " << (*point)[2] << ")" << endl;
}
