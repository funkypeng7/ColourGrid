// Currently outputs to a .txt file read by unity
// Will output to LEDs in final version

// basic file operations
#include <iostream>
#include <fstream>
#include "display.h"
#include "functions.h"

using namespace std;

int outputLEDs(unsigned long colours[][8]) {
  ofstream myfile;
  myfile.open ("./Led grid simulator/Assets/Colours.txt");
  for(int y = 0; y < 8; y++)
  {
    for(int x = 0; x < 10; x++)
    {
      myfile << createHexString(colours[x][y]);
    }
  }
  myfile.close();
  return 0;
}