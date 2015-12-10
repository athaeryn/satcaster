#include "Buffer.h"

Buffer::Buffer(int width, int height) {
  w = width;
  h = height;
  int pixelCount = width * height;
  data = new int [width * height] ();
}

int& Buffer::operator[] (int index) const {
  return data[index];
}

Buffer::~Buffer() {
  delete[] data;
}
