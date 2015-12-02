#ifndef BUFFER_H
#define BUFFER_H

class Buffer {
public:
  Buffer(int w, int h);
  int w;
  int h;
  int *data;
  ~Buffer();
};

#endif
