// Header Files
#include "display.h"
#include "functions.h"
#include "touchSensor.h"
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

// Jagged array of colours in hexidecimal form
unsigned long colours[10][8];

// Mouse/Touch coordinates when [0] == 1 means pressed
vector<int> prevCoords = {0,0,0};

// int getTimeSince()
// {
//     auto begin = chrono::high_resolution_clock::now();    
//     int x;
//     cin >> x;      // wait for user input
//     auto end = chrono::high_resolution_clock::now();    
//     auto dur = end - begin;
//     auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
//     return ms;
// }

// Set all colours to black
void intializeColours() 
{
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            colours[x][y] = createRGB(0,0,0);
        }
    }
}

int main()
{   
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    intializeColours();
    outputLEDs(colours);
    while(true)
    {
        vector<int> vec = getCoordsOfMouse();
        cout << vec[0] << ", " << vec[1] << ", " << vec[2] << "\n";
        if(vec[0] == 1)
        {
            if(prevCoords[0] == 1)
                colours[prevCoords[1]][prevCoords[2]] = createRGB(0,0,0);
            colours[vec[1]][vec[2]] = createRGB(255, 255, 255);
        }
        else if(vec[0] == 0 && prevCoords[0] == 1)
        {
            colours[prevCoords[1]][prevCoords[2]] = createRGB(0,0,0);
        }
        prevCoords = vec;
        outputLEDs(colours);
        sleep_for(milliseconds(10));
    }
    return 0;
}



