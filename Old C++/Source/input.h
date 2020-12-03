#ifndef INPUT_H_
#define INPUT_H_
#include "input.h"
#include "touchSensor.h"

#include <iostream>
#include <vector>
// Main input class
class Input
{

    public:

    bool clickStart = false; // True when click is first registered
    bool click = false; // True when click is happening
    bool clickExit = false; // True when click is let go

    struct intCoords {
        int x = 0, y = 0;
    };
    struct floatCoords{
        float x = 0, y = 0;
    };

    intCoords coords;
    floatCoords rawCoords = {0,0};
    intCoords prevCoords = {0,0};
    floatCoords prevRawCoords = {0,0};

    Input()
    {
        coords = {0, 0};
        rawCoords = {0, 0};
        prevCoords = {0, 0};
        prevRawCoords = {0, 0};

        clickStart = false;
        click = false;
        clickExit = false;

        UpdateInput();
    }

    void UpdateInput(){
        prevCoords = coords;
        prevRawCoords = rawCoords;
    
        std::vector<int> tempCoords = getCoordsOfMouse();
        std::vector<float> tempRawCoords = getRawCoordsOfMouse();

        coords.x = tempCoords[1];
        coords.y = tempCoords[2];
        rawCoords.x = tempRawCoords[1];
        rawCoords.y = tempRawCoords[2];

        clickStart = !click && tempCoords[0] == 1; // If new click start
        clickExit = click && tempCoords[0] == 0; // If click finishes
        click = tempCoords[0] == 1; // If click

        // Debug
        if(clickStart)
            std::cout << "Click Start\n";
        if(click)
            std::cout << "Click\n";
        if(clickExit)
            std::cout << "Click Exit\n";

        std::cout << " {" << tempCoords[0] << ", " << coords.x << ", " << coords.y << "}\n";
        std::cout << " {" << tempRawCoords[0] << ", " << rawCoords.x << ", " << rawCoords.y << "}\n";
    }
};
#endif