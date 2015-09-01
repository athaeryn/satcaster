#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "Vec3.h"

using namespace std;
using namespace vec;

struct Sphere {
  Vec3 pos;
  float r;
};

struct Camera {
  Vec3 pos;
  Vec3 dir;
};

bool does_intersect(Vec3 start, Vec3 dir, Sphere sphere) {
  Vec3 displacement = sub(sphere.pos, start);
  float a = mag_sq(dir);
  float b = 2 * dot(dir, displacement);
  float c = mag_sq(displacement) - pow(sphere.r, 2);
  float radicand = b * b - 4 * a * c;
  return radicand >= 0;
}

void render(int buffer[], int w, int h, Camera camera, vector<Sphere> spheres) {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      float nx = (2 * (x + .5) / w) - 1;
      float ny = 1 - (2 * (y + .5) / h);
      Vec3 ray = norm(add(add(vec::make(nx, ny, 0), camera.pos), camera.dir));

      bool intersects = false;
      for (Sphere s : spheres) {
        if (does_intersect(camera.pos, ray, s)) {
          intersects = true;
        }
      }
      buffer[y * w + x] = intersects ? 1 : 0;
    }
  }
}

int main() {
  vector<Sphere> spheres;
  Sphere sphere1 = {vec::make(0, 0, -10), 4};
  spheres.push_back(sphere1);

  Sphere sphere2 = {vec::make(8, 4, -13), 1};
  spheres.push_back(sphere2);

  Camera cam = {
    vec::make(0, 0, 0), // pos
    vec::make(0, 0, -1) // dir
  };

  int w = 500;
  int h = 500;
  int buffer[w * h];
  render(buffer, w, h, cam, spheres);

  ofstream renderFile;
  string timestamp = to_string(time(0));
  string filename = "./renders/" + timestamp + ".pbm";
  renderFile.open(filename);
  renderFile << "P1" << endl;
  renderFile << "# rendered at " << timestamp << endl;
  renderFile << w << " " << h << endl;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      // 0 is 1 and 1 is 0, because pbm
      renderFile << " " << (buffer[y * w + x] > 0 ? 0 : 1);
    }
    renderFile << endl;
  }
  renderFile.close();

  return 0;
}

