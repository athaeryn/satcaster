#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include "Vec3.h"
#include "Satcaster.h"

using namespace std;


struct Config {
  Camera camera;
  vector<Sphere> spheres;
  int height;
  int width;
};

string write_pbm(int buffer[], int w, int h) {
  ostringstream pbm;
  pbm << "P1" << endl;
  pbm << "#" << endl;
  pbm << w << " " << h << endl;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      pbm << " " << (buffer[y * w + x] > 0 ? 0 : 1); // Black is 1 in PBM...
    }
    pbm << endl;
  }
  return pbm.str();
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
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <scene_file>" << endl;
    return 1;
  }

  const char *configFilename = argv[1];

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
  cout << write_pbm(buffer, w, h);

  return 0;
}

