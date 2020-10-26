// Header Files
#include "global.h"
#include "display.h"
#include "functions.h"
#include "touchSensor.h"
#include "snake.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>

// Global variables
// Containing what is in each cell
char gridInfo[10][8];
// Jagged array of colours in hexidecimal form
unsigned long colours[10][8];
// Mouse/Touch last coordinates when [0] == 1 means pressed
std::vector<int> prevCoords = {0,0,0};
std::vector<float> prevRawCoords = {0,0,0};
// Paths for output and input files
std::string outputFile = "Programming/Colours.txt";
std::string inputFile = "Programming/MousePos.txt";

// Local Variables
//Programs: 1-Snake, 2-Checkers, 3-Rush Hour, 4-Invaders
unsigned long programs[4] = {createRGB(150, 242, 19), createRGB(255, 0, 0), createRGB(0, 0, 255), createRGB(0, 255, 255)};
int numOfPrograms = 4;

// Game info
int currentProgram = -1; 
bool programLoaded = false;

// Set all cells to a colour
void setAllColours(unsigned long colour) 
{
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            colours[x][y] = colour;
        }
    }
}

void Setup()
{
    setAllColours(createRGB(0,0,0));
    outputLEDs(colours);
}

void Loop()
{
    // Get touch position
    std::vector<int> vec = getCoordsOfMouse();

    // Run function for current game
    switch(currentProgram)
    {
        // Game select screen
        case -1:
            // On click 
            if(vec[0] == 1)
            {
                // Calculate index of the selected game based off coords
                int gameIndex = vec[1] + (7 - vec[2]) * 10;
                // If valid game start game
                if(gameIndex < numOfPrograms)
                {
                    currentProgram = gameIndex;
                    Loop();
                    return;
                }
            }
            
            // Display game icons/colours 
            setAllColours(createRGB(0,0,0));
            for(int i = 0; i < numOfPrograms; i++)
            {
                // Starting top left (0, 7) move across to the right and once row is completed move down one
                colours[i - (int)(floor(i/10)) * 10][7 - (int)floor(i/10)] = programs[i];
            }
            break;

    // Snake
    case 0:
        if(!programLoaded)
        {
            std::cout << "Snake\n";
            SnakeInit();
            programLoaded = true;
        }
        Snake();
        break;

    default:
            currentProgram = -1;
            Loop();
            return;
    }
    prevCoords = vec;
    outputLEDs(colours);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

// Main Loop
// Structure 
// Setup() Once
// Loop() Continously
int main()
{   
    Setup();
    while(true)
    {
        Loop();
    }
    return 0;
}



