#include <iostream>
#include <Eigen/Dense>

#include "Sphere.h"
#include "Camera.h"

int main() {
  Sphere sphere(Vector3f(0, 0, 0), 1);
  Camera camera(Vector3f(0, 0, 10));

  cout << sphere.to_string() << endl;
  cout << camera.to_string() << endl;

  Vector3f lookTarget(1, 0, 0);
  camera.lookAt(&lookTarget);
  return 0;
}

