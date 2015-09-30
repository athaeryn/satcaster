#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <regex>

#include "EasyBMP.h"
#include "Vec3.h"
#include "Satcaster.h"

using namespace std;


struct Config {
  Camera camera;
  vector<Sphere> spheres;
  int height;
  int width;
};


void write_bitmap(string filename, int buffer[], int w, int h) {
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
  out.WriteToFile(filename.c_str());
}


Config read_config(const string filename) {
  ifstream configFile(filename);

  regex comment("^#.*$");
  regex dimensions("^([[:digit:]]+) +([[:digit:]]+)$");
  string num = "([-.[:digit:]]+)";
  string triple = "\\(" + num + ", " + num + ", " + num + "\\)";
  regex camera("^" + triple + " " + triple + " " + num + "$");
  regex planet("^" + triple + " " + num + " (.*)$");

  Config conf;

  for (string line; getline(configFile, line);) {
    if (line.empty() || regex_match(line, comment)) continue;
    smatch capture;
    if (regex_match(line, capture, dimensions)) {
      int width = stoi(capture[1].str());
      int height = stoi(capture[2].str());
      conf.height = height;
      conf.width = width;
    } else if (regex_match(line, capture, camera)) {
      conf.camera.pos.x = stof(capture[1].str());
      conf.camera.pos.y = stof(capture[2].str());
      conf.camera.pos.z = stof(capture[3].str());
      conf.camera.dir.x = stof(capture[4].str());
      conf.camera.dir.y = stof(capture[5].str());
      conf.camera.dir.z = stof(capture[6].str());
      conf.camera.fov = stof(capture[7].str());
    } else if (regex_match(line, capture, planet)) {
      Vec3 pos;
      pos.x = stof(capture[1].str());
      pos.y = stof(capture[2].str());
      pos.z = stof(capture[3].str());
      float r = stof(capture[4].str());
      string seed = capture[5].str();
      Sphere s(pos, r, seed);
      conf.spheres.push_back(s);
    } else {
      cerr << "Couldn't parse line: " << line << endl;
    }
  }
  return conf;
}


int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <scene_file> <output_path>" << endl;
    return 1;
  }

  const char *configFilename = argv[1];
  string renderFilename(argv[2]);

  Config config = read_config(configFilename);

  int w = config.width;
  int h = config.height;
  int buffer[w * h];

  Satcaster satcaster;
  satcaster.camera = config.camera;
  for (Sphere s: config.spheres) {
    satcaster.add_body(s.pos.x, s.pos.y, s.pos.z, s.r, s.seed);
  }
  satcaster.render(buffer, w, h);
  write_bitmap(renderFilename, buffer, w, h);

  return 0;
}

