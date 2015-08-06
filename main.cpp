#include <iostream>
#include <Eigen/Dense>

#include "Sphere.h"
#include "Camera.h"

int main() {
  Sphere sphere(0, 0, 0);
  Camera camera(0, 0, 10);

  cout << "Sphere position: " << sphere.get_position_string() << endl;
  cout << "Camera position: " << camera.get_position_string() << endl;

  Vector3f lookTarget(0, 0, 0);
  camera.lookAt(&lookTarget);
  return 0;
}

