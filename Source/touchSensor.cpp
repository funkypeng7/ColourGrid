// Currently takes mouse position from unity
// Will take touch position from capacitive touch sensor

#include "global.h"
#include "touchSensor.h"

#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

std::vector<int> getCoordsOfMouse()
{
    std::string contents; 
    std::ifstream myfile;
    myfile.open (inputFile);
    getline(myfile, contents);
    myfile.close();
    
    if(contents == "")
        return prevCoords;

    std::vector<double> vecD;
    // cout << "In function: " << contents.substr(0, contents.find(',')) << "\n";
    // cout << contents.substr(contents.find(',')) << "\n";

    try {
        vecD = {stod(contents.substr(0, contents.find(','))), stod(contents.substr(contents.find(',') + 1))};
    }
    catch(...)
    {
        return prevCoords;
    }
    std::cout << vecD[0] << ", " << vecD[1] << "\n";
    if(vecD[0] > 5000 || vecD[1] > 5000)
        return {0,0,0};

    int xCoord = floor(vecD[0]/105);
    int yCoord = floor(vecD[1]/105);

    return {1, xCoord, yCoord};
}