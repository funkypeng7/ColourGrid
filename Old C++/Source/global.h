#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <vector>
#include "input.h"

// Define global varibles with extern in here
// Declare with values in main.cpp
extern Input input;

extern std::string outputFile;
extern std::string inputFile;

extern char gridInfo[10][8];

extern unsigned long colours[10][8];
extern std::vector<int> prevCoords;
extern std::vector<float> prevRawCoords;

extern bool programLoaded;
extern int currentProgram;

void setAllColours(unsigned long);
void returnToMainMenu();

#endif

