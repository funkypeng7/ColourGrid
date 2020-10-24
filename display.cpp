// Currently outputs to a .txt file read by unity
// Will output to LEDs in final version

// basic file operations
#include <iostream>
#include <fstream>
#include "display.h"

using namespace std;

int outputLEDs(string msg) {
  ofstream myfile;
  myfile.open ("./Led grid simulator/Assets/output.txt");
  myfile << msg;
  myfile.close();
  return 0;
}