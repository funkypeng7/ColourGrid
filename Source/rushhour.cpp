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

std::vector<std::vector<int>> EASY1 {{1, 0, 2, 4, 2, 4, 3}, {2, 1, 2, 1, 2, 1, 3}};

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
        for(j = 0; j < 7; j++) {
            gridInfo[i][j] = 'SPACE';
        }
    }

    for(i = 1; i < 9; i++) {
        for(j= 0; j < 7; j++) {
            gridInfo[i][j] = 'WALL';
        }
    }

    gridInfo[8][3] = 'EXIT';
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

            }
        }
    }
}

void AddCars()
{
    int i;

    for(i = 0; i < 2; i++) {

        int j;
        int colour = EASY1[i][0];
        int orientation = EASY1[i][1];
        int size = EASY1[i][2];
        int row = EASY1[i][3];
        int col = EASY1[i][4];

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

void Rushhour()
{
    AddCars();
    PrintBoard();
}