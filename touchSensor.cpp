// Currently takes mouse position from unity
// Will take touch position from capacitive touch sensor


#include "touchSensor.h"
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

std::vector<int> getCoordsOfMouse()
{
    string contents; 
    ifstream myfile;
    myfile.open ("./Led grid simulator/Assets/MousePos.txt");
    getline(myfile, contents);
    myfile.close();
    
    if(contents == "")
        return {0,0,0};

    vector<double> vecD;
    // cout << "In function: " << contents.substr(0, contents.find(',')) << "\n";
    // cout << contents.substr(contents.find(',')) << "\n";

    vecD = {stod(contents.substr(0, contents.find(','))), stod(contents.substr(contents.find(',') + 1))};
    cout << vecD[0] << ", " << vecD[1] << "\n";
    if(vecD[0] > 5000 || vecD[1] > 5000)
        return {0,0,0};

    int xCoord = floor(vecD[0]/105);
    int yCoord = floor(vecD[1]/105);

    return {1, xCoord, yCoord};
}