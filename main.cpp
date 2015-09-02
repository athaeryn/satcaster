#include <cmath>

#include "EasyBMP.h"
#include "Satcaster.h"

using namespace std;


void write_bitmap(int buffer[], int w, int h) {
  BMP out;
  out.SetSize(w, h);
  out.SetBitDepth(1);

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      int value = buffer[y * w + x] > 0 ? 255 : 0;
      RGBApixel p;
      p.Red = value;
      p.Blue = value;
      p.Green = value;
      out.SetPixel(x, y, p);
    }
  }
  string timestamp = to_string(time(0));
  string filename = "./renders/" + timestamp + ".bmp";
  out.WriteToFile(filename.c_str());
}


int main() {
  int w = 500;
  int h = 500;
  int buffer[w * h];

  Satcaster satcaster;
  // satcaster.camera.fov = 60;
  satcaster.add_body(0, 0, -20, 4);
  satcaster.add_body(2, 8, -21, 1);
  satcaster.render(buffer, w, h);

  write_bitmap(buffer, w, h);

  return 0;
}

