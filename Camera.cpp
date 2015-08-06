#include "Camera.h"

Camera::Camera(Vector3f center) {
  pos = center;
  lookTarget = Vector3f(0, 0, 0);
}

string Camera::to_string() {
  return "<Camera pos:[" + std::to_string(pos[0])
      +  ", " + std::to_string(pos[1])
      +  ", " + std::to_string(pos[2]) + "]>";
}

void Camera::lookAt(const Vector3f *point) {
  lookTarget = *point;
}
