#include "Buffer.h"

Buffer::Buffer(int width, int height) {
  w = width;
  h = height;
  int pixelCount = width * height;
  data = new int [width * height];
  for (int i = 0; i < pixelCount; i++) {
    data[i] = 0;
  }
}

Buffer::~Buffer() {
  delete data;
}
