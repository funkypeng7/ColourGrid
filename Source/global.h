#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <vector>

// Define global varibles with extern in here
// Declare with values in main.cpp

extern std::string outputFile;
extern std::string inputFile;

extern char gridInfo[10][8];

extern unsigned long colours[10][8];
extern std::vector<int> prevCoords;


void setAllColours(unsigned long);

#endif

