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
// Turquoise = 12 (0, 153, 153)

std::vector<std::vector<int>> EASY1 {{1, 1, 2, 4, 2, 4, 3}, {2, 1, 2, 1, 2, 1, 3}, {3, 1, 3, 3, 2, 3, 4}, {4, 0, 2, 6, 2, 5, 2}, {5, 0, 2, 5, 5, 4, 5}, {6, 0, 2, 2, 4, 1, 4}, {7, 0, 3, 5, 7, 3, 7}, {8, 1, 2, 2, 6, 2, 7}, {9, 1, 3, 6, 5, 6, 7}, {10, 1, 2, 1, 5, 1, 6}, {11, 0, 2, 4, 6, 3, 6}};
std::vector<std::vector<int>> EASY2 {{1, 1, 2, 4, 3, 4, 4}, {4, 1, 2, 3, 3, 3, 4}, {5, 0, 2, 2, 3, 1, 3}, {7, 0, 3, 3, 7, 1, 7}, {9, 0, 3, 4, 5, 2, 5}, {11, 1, 2, 1, 4, 1, }};
std::vector<std::vector<int>> EASY3 {{1, 1, 2, 4, 3, 4, 4}, {3, 1, 3, 3, 5, 3, 6}, {4, 0, 2, 3, 4, 2, 4}, {5, 0, 2, 2, 7, 1, 7}, {7, 0, 3, 6, 5, 4, 5}, {8, 1, 2, 2, 6, 2, 7}, {9, 1, 3, 6, 5, 6, 7}, {10, 1, 2, 1, 5, 1, 6}, {11, 0, 2, 4, 6, 3, 6}};

void RushhourInit()
{
    int i, j;

    for(i = 1; i < 8; i++) {
        gridInfo[0][i] = 'SIDE';
    }
 
    for(i = 1; i < 8; i++) {
        gridInfo[9][i] = 'SIDE';
    }

    gridInfo[0][0] = 'CLICKLEFT';
    gridInfo[9][0] = 'CLICKRIGHT';

    for(i = 1; i < 9; i++) {
        for(j= 0; j < 7; j++) {
            gridInfo[i][j] = 'WALL';
        }
    }

    for(i = 2; i < 8; i++) {
        for(j = 1; j < 6; j++) {
            gridInfo[i][j] = 'SPACE';
        }
    }

    gridInfo[8][4] = 'EXIT';
}

void AddCars(std::vector<std::vector<int>> CHOSENBOARD)
{
    int i;

    for(i = 0; i < size(CHOSENBOARD); i++) {

        int j;
        int colour = CHOSENBOARD[i][0];
        int orientation = CHOSENBOARD[i][1];
        int size = CHOSENBOARD[i][2];
        int row = CHOSENBOARD[i][3];
        int col = CHOSENBOARD[i][4];

        if (orientation == 1) {
		    for (j = col; j <= (col + size - 1 ); j++) {

			    gridInfo[row][j] = colour;
		    }
        } else {
            for (j = row; j <= (row + - 1 * size - 1); j++) {

			    gridInfo[j][col] = colour;
		    }
        }
	}

}

void PrintBoard()
{
    int i, j;

    for(i = 0; i < 10; i++) {
        for(j = 0; j < 7; j++) {

            switch(gridInfo[i][j])
            {
                case 'SIDE':
                    colours[i][j] = createRGB(102, 178, 255);
                    break;
                case 'CLICKLEFT':
                    colours[i][j] = createRGB(255, 102, 102);
                    break;
                case 'CLICKRIGHT':
                    colours[i][j] = createRGB(102, 255, 102);
                    break;
                case 'WALL':
                    colours[i][j] = createRGB(64, 64, 64);
                    break;
                case 'SPACE':
                    colours[i][j] = createRGB(160, 160, 160);
                    break;
                case 'EXIT':
                    colours[i][j] = createRGB(160, 160, 160);
                    break;  
                case 1:
                    colours[i][j] = createRGB(255, 0, 0);
                    break;
                case 2:
                    colours[i][j] = createRGB(0, 204, 0);
                    break;
                case 3:
                    colours[i][j] = createRGB(0, 0, 255);
                    break;
                case 4:
                    colours[i][j] = createRGB(0, 255, 128);
                    break;
                case 5:
                    colours[i][j] = createRGB(255, 153, 51);
                    break;
                case 6:
                    colours[i][j] = createRGB(255, 153, 204);
                    break;
                case 7:
                    colours[i][j] = createRGB(204, 153, 255);
                    break;
                case 8:
                    colours[i][j] = createRGB(127, 0, 255);
                    break;
                case 9:
                    colours[i][j] = createRGB(255, 255, 51);
                    break;
                case 10:
                    colours[i][j] = createRGB(0, 0, 0);
                    break;
                case 11:
                    colours[i][j] = createRGB(153, 255, 255);
                    break;
                case 12:
                    colours[i][j] = createRGB(0, 153, 153);
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