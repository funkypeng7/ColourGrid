// Currently outputs to a .txt file read by unity
// Will output to LEDs in final version

#include "display.h"
#include "functions.h"
#include "global.h"

#include <iostream>
#include <fstream>
#include <string>

int outputLEDs(unsigned long colours[][8]) {
  std::cout << "Trying to output LEDs\n";
  std::ofstream myfile;
  myfile.open(outputFile);
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