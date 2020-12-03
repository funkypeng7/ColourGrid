// Header Files
#include "global.h"
#include "display.h"
#include "functions.h"
#include "touchSensor.h"
// Games
#include "snake.h"
#include "rushhour.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>

// Global variables
// Input object
Input input = Input();
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
// Game info
bool programLoaded = false;
int currentProgram = -1;

// Local Variables
//Programs: 1-Snake, 2-Checkers, 3-Rush Hour, 4-Invaders
unsigned long programs[4] = {createRGB(150, 242, 19), createRGB(255, 0, 0), createRGB(0, 0, 255), createRGB(0, 255, 255)};
int numOfPrograms = 4;




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

void returnToMainMenu()
{
    currentProgram = -1;
    programLoaded = false;
}

void Setup()
{
    setAllColours(createRGB(0,0,0));
    outputLEDs(colours);
}

void Loop()
{
    input.UpdateInput();

    // Run function for current game
    switch(currentProgram)
    {
        // Game select screen
        case -1:
            // On click 
            if(input.clickStart)
            {
                
                // Calculate index of the selected game based off coords
                int gameIndex = input.coords.x + (7 - input.coords.y) * 10;
                std::cout << "Coords of click " << input.coords.x << ", " << input.coords.y << "\n";
                std::cout << "Select Game " << gameIndex << "\n";
                // If valid game start game
                if(gameIndex < numOfPrograms)
                {
                    currentProgram = gameIndex;
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
                SnakeSelect();
            else
                Snake();
            break;

        // Rush Hour
        case 2:
            Rushhour();
            break;

        default:
            currentProgram = -1;
            Loop();
            return;
    }
    outputLEDs(colours);
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



