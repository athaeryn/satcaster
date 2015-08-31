#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Vec3 {
  float x;
  float y;
  float z;
};

struct Sphere {
  Vec3 pos;
  float r;
};

struct Camera {
  Vec3 pos;
  Vec3 dir;
};

Vec3 vec(float x, float y, float z) {
  Vec3 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

Vec3 vec_add(Vec3 a, Vec3 b) {
  Vec3 c;
  c.x = a.x + b.x;
  c.y = a.y + b.y;
  c.z = a.z + b.z;
  return c;
}

Vec3 vec_sub(Vec3 a, Vec3 b) {
  Vec3 c;
  c.x = a.x - b.x;
  c.y = a.y - b.y;
  c.z = a.z - b.z;
  return c;
}

float vec_mag_sq(Vec3 v) {
  return pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
}

float vec_mag(Vec3 v) {
  return sqrt(vec_mag_sq(v));
}

float vec_dot(Vec3 a, Vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec_norm(Vec3 v) {
  float mag = vec_mag(v);
  Vec3 normed;
  normed.x = v.x / mag;
  normed.y = v.y / mag;
  normed.z = v.z / mag;
  return normed;
}

bool does_intersect(Vec3 start, Vec3 dir, Sphere sphere) {
  Vec3 displacement = vec_sub(sphere.pos, start);
  float a = vec_mag_sq(dir);
  float b = 2 * vec_dot(dir, displacement);
  float c = vec_mag_sq(displacement) - pow(sphere.r, 2);
  float radicand = b * b - 4 * a * c;
  return radicand >= 0;
}

void render(int buffer[], int w, int h, Camera camera, vector<Sphere> spheres) {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      float nx = (2 * (x + .5) / w) - 1;
      float ny = 1 - (2 * (y + .5) / h);
      Vec3 ray = vec_norm(vec_add(vec_add(vec(nx, ny, 0), camera.pos), camera.dir));

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
  Sphere sphere1 = {vec(0, 0, -10), 4};
  spheres.push_back(sphere1);

  Sphere sphere2 = {vec(8, 4, -13), 1};
  spheres.push_back(sphere2);

  Camera cam = {
    vec(0, 0, 0), // pos
    vec(0, 0, -1) // dir
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

