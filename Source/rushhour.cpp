#include "global.h"
#include "functions.h"
#include "rushhour.h"
#include "touchSensor.h"

#include <iostream>
#include <stdio.h>

// 0 - Select Difficulty, 1 - Select Map, 2 - Play game
int gameState = 0;
int boardChosen = 1;
int difficultyChosen;
std::vector<std::vector<int>> currentBoard;

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
// Tan = 13
// Olive = 14
// Pale Yellow = 15
// Brown = 16

std::vector<std::vector<int>> EASY1 {{1, 1, 2, 2, 4, 3, 4}, {2, 1, 2, 2, 1, 3, 1}, {3, 1, 3, 2, 3, 4, 3}, {4, 0, 2, 2, 5, 2, 6}, {5, 0, 2, 5, 4, 5, 5}, {6, 0, 2, 4, 1, 4, 2}, {7, 0, 3, 7, 3, 7, 5}, {8, 1, 2, 6, 2, 7, 2}, {9, 1, 3, 5, 6, 7, 6}, {10, 1, 2, 5, 1, 6, 1}, {11, 0, 2, 6, 3, 6, 4}};
std::vector<std::vector<int>> EASY2 {{1, 1, 2, 3, 4, 4, 4}, {4, 1, 2, 3, 3, 4, 3}, {5, 0, 2, 3, 1, 3, 2}, {7, 0, 3, 7, 1, 7, 3}, {9, 0, 3, 5, 2, 5, 4}, {11, 1, 2, 4, 1, 5, 1}};
std::vector<std::vector<int>> EASY3 {{1, 1, 2, 3, 4, 4, 4}, {3, 1, 3, 5, 3, 6, 3}, {4, 0, 2, 4, 2, 4, 3}, {5, 0, 2, 7, 1, 7, 2}, {7, 0, 3, 5, 4, 5, 6}, {9, 0, 3, 2, 4, 2, 6}, {12, 1, 3, 4, 1, 6, 1}};
std::vector<std::vector<int>> EASY4 {{1, 1, 2, 3, 4, 4, 4}, {2, 1, 2, 6, 1, 7, 1}, {3, 0, 3, 6, 3, 6, 5}, {4, 1, 2, 2, 6, 3, 6}, {5, 0, 2, 7, 5, 7, 6}, {6, 0, 2, 2, 1, 2, 2}, {7, 0, 3, 2, 3, 2, 5}, {8, 1, 2, 6, 2, 7, 2}, {9, 0, 3, 5, 4, 5, 6}, {10, 0, 2, 7, 3, 7, 4}, {12, 1, 3, 3, 3, 6, 3}};
std::vector<std::vector<int>> MED1 {{1, 1, 2, 3, 4, 4, 4}, {3, 1, 3, 5, 3, 7, 3}, {4, 1, 2, 3, 6, 4, 6}, {5, 0, 2, 4, 2, 4, 3}, {7, 0, 3, 5, 4, 5, 6}, {8, 0, 2, 7, 1, 7, 2}, {9, 0, 3, 2, 4, 2, 6}, {12, 1, 3, 4, 1, 6, 1}};
std::vector<std::vector<int>> MED2 {{1, 1, 2, 2, 4, 3, 4}, {3, 1, 3, 5, 3, 7, 3}, {4, 0, 2, 2, 5, 2, 6}, {5, 1, 2, 3, 6, 4, 6}, {7, 0, 3, 4, 3, 4, 6}, {9, 0, 3, 7, 4, 7, 6}, {11, 0, 2, 6, 1, 6, 2}, {12, 1, 3, 2, 1, 3, 1}};
std::vector<std::vector<int>> MED3 {{1, 1, 2, 5, 4, 6, 4}, {2, 1, 2, 5, 3, 6, 3}, {4, 1, 2, 2, 6, 3, 6}, {5, 1, 2, 4, 6, 5, 6}, {6, 0, 2, 4, 4, 4, 5}, {7, 0, 3, 2, 1, 2, 3}, {8, 0, 2, 3, 3, 3, 4}, {9, 0, 3, 7, 3, 7, 5}, {10, 0, 2, 5, 1, 5, 2}, {11, 0, 2, 6, 5, 6, 6}, {13, 1, 2, 6, 2, 7, 2}, {14, 1, 2, 6, 1, 7, 1}, {15, 1, 2, 3, 1, 4, 1}};
std::vector<std::vector<int>> MED4 {{1, 1, 2, 4, 4, 5, 4}, {2, 0, 2, 6, 3, 6, 4}, {4, 1, 2, 2, 6, 3, 6}, {5, 0, 2, 4, 5, 4, 6}, {6, 0, 2, 2, 3, 2, 4}, {8, 0, 2, 3, 3, 3, 4}, {10, 0, 2, 7, 3, 7, 4}, {11, 1, 2, 6, 5, 7, 5}, {13, 1, 2, 4, 3, 5, 3}, {14, 1, 2, 2, 1, 3, 1}, {15, 0, 2, 4, 1, 4, 2}, {16, 1, 2, 6, 2, 7, 2}};
std::vector<std::vector<int>> HARD1 {{1, 1, 2, 3, 4, 4, 4}, {3, 1, 3, 3, 3, 5, 3}, {4, 1, 2, 2, 6, 3, 6}, {5, 0, 2, 4, 5, 4, 6}, {7, 0, 3, 2, 3, 2, 5}, {9, 0, 3, 5, 4, 5, 6}, {12, 1, 3, 5, 1, 7, 1}};
std::vector<std::vector<int>> HARD2 {{1, 1, 2, 3, 4, 4, 4}, {2, 0, 2, 2, 1, 2, 2}, {3, 1, 3, 3, 1, 5, 1}, {4, 0, 2, 4, 5, 4, 6}, {5, 0, 2, 2, 4, 2, 5}, {6, 0, 2, 3, 2, 3, 3}, {7, 0, 3, 5, 3, 5, 5}, {8, 1, 2, 6, 3, 7, 3}, {9, 1, 3, 5, 6, 7, 6}, {10, 1, 2, 4, 2, 5, 2}, {11, 1, 2, 6, 5, 7, 5}, {13, 0, 2, 7, 1, 7, 2}};
std::vector<std::vector<int>> HARD3 {{1, 1, 2, 5, 4, 6, 4}, {2, 1, 2, 6, 2, 7, 2}, {3, 1, 3, 4, 1, 6, 1}, {4, 0, 2, 4, 4, 4, 5}, {5, 1, 2, 5, 5, 6, 5}, {6, 0, 2, 5, 2, 5, 3}, {7, 0, 3, 7, 4, 7, 6}, {8, 1, 2, 6, 3, 7, 3}, {9, 1, 3, 4, 6, 6, 6}, {11, 0, 2, 4, 2, 4, 3}};
std::vector<std::vector<int>> HARD4 {{1, 1, 2, 4, 4, 5, 4}, {2, 1, 2, 3, 3, 4, 3}, {4, 0, 2, 4, 5, 4, 6}, {5, 1, 2, 5, 6, 6, 6}, {6, 0, 2, 2, 3, 2, 4}, {8, 0, 2, 6, 3, 6, 4}, {9, 1, 3, 2, 2, 4, 2}, {10, 0, 2, 6, 1, 6, 2}, {11, 0, 2, 3, 4, 3, 5}, {13, 1, 2, 2, 1, 3, 1}};
std::vector<std::vector<int>> XTRME1 {{1, 1, 2, 3, 4, 4, 4}, {2, 1, 2, 2, 2, 3, 2}, {3, 0, 3, 4, 1, 4, 3}, {4, 1, 2, 2, 6, 3, 6}, {5, 0, 2, 5, 4, 5, 5}, {6, 0, 2, 2, 3, 2, 4}, {7, 0, 3, 7, 2, 7, 4}, {8, 1, 2, 5, 3, 6, 3}, {9, 1, 3, 5, 6, 7, 6}, {11, 1, 2, 6, 5, 6, 6}, {12, 1, 3, 5, 1, 7, 1}};
std::vector<std::vector<int>> XTRME2 {{1, 1, 2, 2, 4, 3, 4}, {2, 1, 2, 5, 3, 6, 3}, {4, 1, 2, 2, 6, 3, 6}, {5, 0, 2, 5, 5, 5, 6}, {6, 0, 2, 2, 2, 2, 3}, {7, 0, 3, 7, 1, 7, 3}, {8, 1, 2, 3, 3, 4, 3}, {9, 0, 3, 4, 4, 4, 6}, {11, 1, 2, 6, 6, 7, 6}, {13, 1, 2, 2, 1, 3, 1}, {14, 0, 2, 5, 1, 5, 2}};
std::vector<std::vector<int>> XTRME3 {{1, 1, 2, 2, 4, 3, 4}, {2, 1, 2, 3, 2, 4, 2}, {3, 1, 3, 2, 1, 4, 1}, {4, 0, 2, 3, 5, 3, 6}, {5, 1, 2, 6, 6, 7, 6}, {6, 1, 2, 3, 3, 4, 3}, {7, 0, 3, 7, 1, 7, 3}, {8, 1, 2, 5, 3, 6, 3}, {10, 0, 2, 5, 1, 5, 2}, {12, 0, 3, 4, 4, 4, 6}, {13, 0, 2, 6, 1, 6, 2}, {15, 0, 2, 2, 2, 2, 3}};
std::vector<std::vector<int>> XTRME4 {{1, 1, 2, 2, 4, 3, 4}, {2, 1, 2, 6, 2, 7, 2}, {3, 1, 3, 2, 3, 4, 3}, {4, 0, 2, 2, 5, 2, 6}, {5, 0, 2, 5, 4, 5, 5}, {6, 0, 2, 5, 2, 5, 3}, {7, 0, 3, 7, 3, 7, 5}, {8, 0, 2, 4, 1, 4, 2}, {11, 0, 2, 6, 3, 6, 4}, {12, 1, 3, 5, 6, 7, 6}, {13, 1, 2, 5, 1, 6, 1}, {15, 1, 2, 2, 1, 3, 1}};


void SetUpBoard()
{
    int x, y;

    // sides of board

    for(x = 1; x < 8; x++) {
        gridInfo[0][x] = 'S';
    }
 
    for(x = 1; x < 8; x++) {
        gridInfo[9][x] = 'S';
    }

    // left and right cycle, select current board and return to difficulty selection screen buttons

    gridInfo[0][0] = 'L';
    gridInfo[9][0] = 'R';
    gridInfo[9][7] = 9;
    gridInfo[0][7] = 7;

    // walls of board

    for(x = 1; x < 9; x++) {
        for(y = 0; y < 8; y++) {
            gridInfo[x][y] = 'W';
        }
    }

    // game board road

    for(x = 2; x < 8; x++) {
        for(y = 1; y < 7; y++) {
            gridInfo[x][y] = 'B';
        }
    }

    // road exit

    gridInfo[8][4] = 'E';
}

void AddCars(std::vector<std::vector<int>> CHOSENBOARD)
{
    int i;

    for(i = 0; i < (int)size(CHOSENBOARD); i++) {

        int x, y;
        int colour = CHOSENBOARD[i][0];
        int orientation = CHOSENBOARD[i][1];
        int size = CHOSENBOARD[i][2];
        int row = CHOSENBOARD[i][3];
        int col = CHOSENBOARD[i][4];

        // if car is vertical

        if (orientation == 0) {
		    for ( y = col; y <= (col + size - 1); y++) {

			    gridInfo[row][y] = colour;
		    }
        } 
        
        // if car is horizontal
        
        else {
            for (x = row; x <= (row + size - 1); x++) {

			    gridInfo[x][col] = colour;
		    }
        }
	}

    currentBoard = CHOSENBOARD;

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
                case 0:
                    colours[x][y] = createRGB(0, 0, 0);
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
                case 13:
                    colours[x][y] = createRGB(255, 229, 204);
                    break;
                case 14:
                    colours[x][y] = createRGB(0, 51, 25);
                    break;
                case 15:
                    colours[x][y] = createRGB(255, 255, 153);
                    break;
                case 16:
                    colours[x][y] = createRGB(153, 76, 0);
                    break;

            }
        }
    }
}

void BoardSelection(int Difficulty, int boardNumber)
{  
    SetUpBoard();

    std::vector<int> coords = getCoordsOfMouse();
    if(prevCoords[0] == 0 && coords[0] == 1) 
    {
        if(coords[1] == 9 && coords[2] == 0) 
        {
            boardNumber++;

            if(boardNumber > 4) {
                boardNumber = boardNumber - 4;
            }
        }
        if(coords[1] == 0 && coords[2] == 0)
        {
            boardNumber--;

            if(boardNumber < 1) {
                boardNumber = boardNumber + 4;
            }
        }
        if(coords[1] == 9 && coords[2] == 7)
        {
            gameState = 2;
        }
    }

    boardChosen = boardNumber;

    switch(Difficulty) 
    {
        case 1:

            switch(boardNumber)
            {
                case 1:
                    AddCars(EASY1);
                    break;

                case 2:
                    AddCars(EASY2);
                    break;

                case 3:
                    AddCars(EASY3);
                    break;
                
                case 4:
                    AddCars(EASY4);
                    break;
            }

            break;

        case 2:

            switch(boardNumber)
            {
                case 1:
                    AddCars(MED1);
                    break;

                case 2:
                    AddCars(MED2);
                    break;

                case 3:
                    AddCars(MED3);
                    break;
                
                case 4:
                    AddCars(MED4);
                    break;
            }

            break;
        
        case 3:

            switch(boardNumber)
            {
                case 1:
                    AddCars(HARD1);
                    break;

                case 2:
                    AddCars(HARD2);
                    break;

                case 3:
                    AddCars(HARD3);
                    break;
                
                case 4:
                    AddCars(HARD4);
                    break;
            }

            break;

        case 4:

            switch(boardNumber)
            {
                case 1:
                    AddCars(XTRME1);
                    break;

                case 2:
                    AddCars(XTRME2);
                    break;

                case 3:
                    AddCars(XTRME3);
                    break;
                
                case 4:
                    AddCars(XTRME4);
                    break;
            }

            break;
    }

}

void ChooseDifficulty()
{
    int x, y;

    for(x = 0; x < 10; x++) {
        for(y = 0; y < 8; y++) {
            gridInfo[x][y] = 0;
        }
    }

    for(x = 1; x <= 2; x++) {
        for(y = 0; y < 8; y++) {
            gridInfo[x][y] = 2;
        }
    }

    for(x = 3; x <= 4; x++) {
        for(y = 0; y < 8; y++) {
            gridInfo[x][y] = 3;
        }
    }

    for(x = 5; x <= 6; x++) {
        for(y = 0; y < 8; y++) {
            gridInfo[x][y] = 5;
        }
    }

    for(x = 7; x <= 8; x++) {
        for(y = 0; y < 8; y++) {
            gridInfo[x][y] = 1;
        }
    }

    PrintBoard();

    std::vector<int> coords = getCoordsOfMouse();
    if(prevCoords[0] == 0 && coords[0] == 1) 
    {
        prevCoords = coords;
        
        gameState = 1;

        if(coords[1] >= 1 && coords[1] < 3) {
            difficultyChosen = 1;
        }
        else if(coords[1] >= 3 && coords[1] < 5) {
            difficultyChosen = 2;
        }
        else if(coords[1] >= 5 && coords[1] < 7) {
            difficultyChosen = 3;

        }
        else if(coords[1] >= 7 && coords[1] < 9) {
            difficultyChosen = 4;
        }
        else {
            gameState = 0;
        }

        
    }
}

void MoveCar()
{
    int i, j;
    int carChosen;
    int distance = 0;
    int direction = 0;
    int carInfo[7];

    // Direction
    // 0 = up
    // 1 = down
    // 2 = left
    // 3 = right

    gridInfo[0][0] = 'S';
    gridInfo[9][0] = 'S';
    gridInfo[9][7] = 'S';

    std::vector<int> coords = getCoordsOfMouse();
    if(prevCoords[0] == 0 && coords[0] == 1)
    {
        std::vector<int> deltaVector = {prevCoords[1] - coords[1], prevCoords[2] - coords[2]};

        // calculate direction mouse has moved, distance (blocks) the mouse haa moved and car clicked on

        if(deltaVector[1] > 1 && deltaVector[0] == 0)
        {
            direction = 0;
            distance = deltaVector[1];
            carChosen = gridInfo[coords[1]][coords[2]];
        }
        else if(deltaVector[1] < 1 && deltaVector[0] == 0)
        {
            direction = 1;
            distance = -1 * deltaVector[1];
            carChosen = gridInfo[coords[1]][coords[2]];
        } 
        else if(deltaVector[0] > 1 && deltaVector[0] == 0)
        {
            direction = 2;
            distance = deltaVector[0];
            carChosen = gridInfo[coords[1]][coords[2]];
        }
        else if(deltaVector[0] < 1 && deltaVector[0] == 0)
        {
            direction = 3;
            distance = -1 * deltaVector[0];
            carChosen = gridInfo[coords[1]][coords[2]];
        }

    }

    // copy car info

    for(i = 0; i < (int)size(currentBoard); i++)
    {
        if (currentBoard[i][0] == carChosen)
        {
            for(j = 0; j < 7; j++)
            {
                carInfo[j] == currentBoard[i][j];
            }
        }
    }

    // move up

    if (direction == 0 && carInfo[1] == 0)
    {
        for (i = 0; i < distance; i++)
        {
            for (j = 0; j < carInfo[2]; j++)
            {
                if(gridInfo[carInfo[5]][carInfo[6] - j + i] == 'B')
                {
                    gridInfo[carInfo[5]][carInfo[6] - j] = 'B';
                    gridInfo[carInfo[5]][carInfo[6] - j + i] = carInfo[0];
                }
            }
        }

        carInfo[4] = gridInfo[carInfo[5]][carInfo[6] - j + i];
        carInfo[6] = gridInfo[carInfo[5]][carInfo[6] + j + i];
    }

    // move down

    if (direction == 1 && carInfo[1] == 0)
    {
        for (i = 0; i < distance; i++)
        {
            for (j = 0; j < carInfo[2]; j++)
            {
                if(gridInfo[carInfo[5]][carInfo[6] + j - i] == 'B')
                {
                    gridInfo[carInfo[5]][carInfo[6] + j] = 'B';
                    gridInfo[carInfo[5]][carInfo[6] + j - i] = carInfo[0];
                }
            }
        }

        carInfo[4] = gridInfo[carInfo[5]][carInfo[6] + j - i];
        carInfo[6] = gridInfo[carInfo[5]][carInfo[6] - j - i];
    }

    // move left

    if (direction == 2 && carInfo[1] == 1)
    {
        for (i = 0; i < distance; i++)
        {
            for (j = 0; j < carInfo[2]; j++)
            {
                if(gridInfo[carInfo[3] + j - 1][carInfo[4]] == 'B')
                {
                    gridInfo[carInfo[3] + j][carInfo[4]] = 'B';
                    gridInfo[carInfo[3] + j - i][carInfo[4]] = carInfo[0];
                }
            }
        }

        carInfo[3] = gridInfo[carInfo[3] + j - i][carInfo[4]];
        carInfo[5] = gridInfo[carInfo[3] - j - i][carInfo[4]];
    }

    // move right

    if (direction == 3 && carInfo[1] == 1)
    {
        for (i = 0; i < distance; i++)
        {
            for (j = 0; j < carInfo[3]; j++)
            {
                if(gridInfo[carInfo[3] - j + 1][carInfo[3]] == 'B')
                {
                    gridInfo[carInfo[3] - j][carInfo[4]] = 'B';
                    gridInfo[carInfo[3] - j + i][carInfo[4]] = carInfo[0];
                }
            }
        }

        carInfo[3] = gridInfo[carInfo[3] - j + i][carInfo[4]];
        carInfo[5] = gridInfo[carInfo[3] + j + i][carInfo[4]];
    }

}

void Rushhour()
{

    switch(gameState)
    {
        case 0:
            ChooseDifficulty();
            break;
        case 1:
            BoardSelection(difficultyChosen, boardChosen);
            // When there is a click on the game board set gameState to 2
            // Save the click position
            break;
        case 2:
            MoveCar();
            // MoveCars() - detct button presses then move
            break;
        
    }

    std::vector<int> coords = getCoordsOfMouse();
    if(prevCoords[0] == 0 && coords[0] == 1)
    {
        if(coords[1] == 0 && coords[2] == 7)
        {
            gameState = 0;
        }
    }

    PrintBoard();
}