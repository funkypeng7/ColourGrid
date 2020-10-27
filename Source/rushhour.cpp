#include "global.h"
#include "functions.h"
#include "rushhour.h"
#include "touchSensor.h"

#include <iostream>
#include <stdio.h>

// Format: {Car Colour, Orientation, Length, Starting Row Number, Starting Column Number, Ending Row Number, Ending Column Number}

// Orientation:
// Vertical = 0
// Horizontal = 1

// Car Colours:
// Red = 1
// Green = 2
// Blue = 3
// Lime = 4
// Orange = 5
// Pink = 6
// Purple = 7
// Indigo = 8
// Yellow = 9
// Black = 10
// Aqua = 11
// Turquoise = 12

std::vector<std::vector<int>> EASY1 {{1, 1, 2, 2, 4, 3, 4}, {2, 1, 2, 2, 1, 3, 1}, {3, 1, 3, 2, 3, 4, 3}, {4, 0, 2, 2, 5, 2, 6}, {5, 0, 2, 5, 4, 5, 5}, {6, 0, 2, 4, 1, 4, 2}, {7, 0, 3, 7, 3, 7, 5}, {8, 1, 2, 6, 2, 7, 2}, {9, 1, 3, 5, 6, 7, 6}, {10, 1, 2, 5, 1, 6, 1}, {11, 0, 2, 6, 3, 6, 4}};
std::vector<std::vector<int>> EASY2 {{1, 1, 2, 3, 4, 4, 4}, {4, 1, 2, 3, 3, 4, 3}, {5, 0, 2, 3, 2, 3, 1}, {7, 0, 3, 7, 3, 7, 1}, {9, 0, 3, 5, 4, 5, 2}, {11, 1, 2, 4, 1, 5, 1}};
std::vector<std::vector<int>> EASY3 {{1, 1, 2, 3, 4, 4, 4}, {3, 1, 3, 5, 3, 6, 3}, {4, 0, 2, 4, 3, 4, 2}, {5, 0, 2, 7, 2, 7, 1}, {7, 0, 3, 5, 6, 5, 4}, {8, 1, 2, 6, 2, 7, 2}, {9, 1, 3, 5, 6, 7, 6}, {10, 1, 2, 5, 1, 6, 1}, {11, 0, 2, 6, 4, 6, 3}};

void RushhourInit()
{
    int x, y;

    for(x = 1; x < 8; x++) {
        gridInfo[x][0] = 'S';
    }
 
    for(x = 1; x < 8; x++) {
        gridInfo[9][x] = 'S';
    }

    gridInfo[0][0] = 'L';
    gridInfo[9][0] = 'R';

    for(x = 1; x < 9; x++) {
        for(y = 0; y < 8; y++) {
            gridInfo[x][y] = 'W';
        }
    }

    for(x = 2; x < 8; x++) {
        for(y = 1; y < 7; y++) {
            gridInfo[x][y] = 'B';
        }
    }

    gridInfo[8][4] = 'E';
}

void AddCars(std::vector<std::vector<int>> CHOSENBOARD)
{
    int i;

    for(i = 0; i < size(CHOSENBOARD); i++) {

        int x, y;
        int colour = CHOSENBOARD[i][0];
        int orientation = CHOSENBOARD[i][1];
        int size = CHOSENBOARD[i][2];
        int row = CHOSENBOARD[i][3];
        int col = CHOSENBOARD[i][4];

        if (orientation == 0) {
		    for ( y = col; y <= (col + size - 1); y++) {

			    gridInfo[row][y] = colour;
		    }
        } else {
            for (x = row; x <= (row + size - 1); x++) {

			    gridInfo[x][col] = colour;
		    }
        }
	}

}

void PrintBoard()
{
    int x, y;

    for(x = 0; x < 10; x++) {
        for(y = 0; y < 8; y++) {

            switch(gridInfo[x][y])
            {
                case 'S':
                    colours[x][y] = createRGB(102, 178, 255);
                    break;
                case 'L':
                    colours[x][y] = createRGB(255, 102, 102);
                    break;
                case 'R':
                    colours[x][y] = createRGB(102, 255, 102);
                    break;
                case 'W':
                    colours[x][y] = createRGB(64, 64, 64);
                    break;
                case 'B':
                    colours[x][y] = createRGB(160, 160, 160);
                    break;
                case 'E':
                    colours[x][y] = createRGB(160, 160, 160);
                    break;  
                case 1:
                    colours[x][y] = createRGB(255, 0, 0);
                    break;
                case 2:
                    colours[x][y] = createRGB(0, 204, 0);
                    break;
                case 3:
                    colours[x][y] = createRGB(0, 0, 255);
                    break;
                case 4:
                    colours[x][y] = createRGB(0, 255, 128);
                    break;
                case 5:
                    colours[x][y] = createRGB(255, 153, 51);
                    break;
                case 6:
                    colours[x][y] = createRGB(255, 153, 204);
                    break;
                case 7:
                    colours[x][y] = createRGB(204, 153, 255);
                    break;
                case 8:
                    colours[x][y] = createRGB(127, 0, 255);
                    break;
                case 9:
                    colours[x][y] = createRGB(255, 255, 51);
                    break;
                case 10:
                    colours[x][y] = createRGB(0, 0, 0);
                    break;
                case 11:
                    colours[x][y] = createRGB(153, 255, 255);
                    break;
                case 12:
                    colours[x][y] = createRGB(0, 153, 153);
                    break;

            }
        }
    }
}

void Rushhour()
{
    AddCars(EASY1);
    PrintBoard();
}