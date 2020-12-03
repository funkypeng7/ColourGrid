#include "global.h"
#include "functions.h"
#include "snake.h"
#include "touchSensor.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

bool alive;

// Time between snake moves in milliseconds
const int millisBetweenMoves = 600;

std::vector<std::vector<int>> snake = {{4, 3}};

int snakeLength = 1;
std::vector<int> apple;

Input::floatCoords initialPress;

// Time Of Last Movement
auto lastMove = std::chrono::high_resolution_clock::now();    

// 0 - up, 1 - right, 2 - down, 3 - left
int direction = 0;
int lastDirectionTraveled = 0;

bool dieOnWall;

// For death
unsigned long deathSave[10][8];
bool isDeathSaveShowing;

// Grid info
// '#' - Empty (white)
// 'S' - Snake (green)
// 'H' - Head of Snake (darker green)
// 'A' - Apple (red)

void GetNewApplePosition()
{
    bool go = true;
    while(go)
    {
        go = false;
        apple = {rand() % 9 + 1, rand() % 7 + 1};
        for(int i = 0; i < snakeLength; i++)
        {
            if(snake[i] == apple)
                go = true;
        }
    }
}

void DrawGrid()
{
    // Set gridInfo to empty with snake and apple
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            gridInfo[x][y] = '#';
        }
    }

    // Draw Snake
    for(int i = 1; i < snakeLength; i++)
    {
        gridInfo[snake[i][0]][snake[i][1]] = 'S';
    }
    // Draw Head
    gridInfo[snake[0][0]][snake[0][1]] = 'H';
    // Draw Apple
    gridInfo[apple[0]][apple[1]] = 'A';
}

void SetSnakeColours()
{
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            switch(gridInfo[x][y])
            {
                // White
                case '#':
                    colours[x][y] = createRGB(255, 255, 255);
                    break;
                case 'S':
                    colours[x][y] = createRGB(150, 242, 19);
                    break;
                case 'H':
                    colours[x][y] = createRGB(100, 150, 0);
                    break;
                case 'A':
                    colours[x][y] = createRGB(255, 20, 20);
                    break;
                

            }
        }
    }
}

void CheckDirection()
{
    // First Press
    if(input.clickStart)
    {
        initialPress = input.rawCoords;

    }
    // Letting go
    if(input.clickExit)
    {
        Input::floatCoords deltaVector = {input.prevRawCoords.x - initialPress.x, input.prevRawCoords.y - initialPress.y};

        // Up
        if(deltaVector.y > 100 && (lastDirectionTraveled != 2 || snakeLength == 1))
            direction = 0;
        // Right
        else if(deltaVector.x > 100 && (lastDirectionTraveled != 3 || snakeLength == 1))
            direction = 1;
        // Down
        else if(deltaVector.y < -100 && (lastDirectionTraveled != 0 || snakeLength == 1))
            direction = 2;
        // Left
        else if(deltaVector.x < -100 && (lastDirectionTraveled != 1 || snakeLength == 1))
            direction = 3;

        lastDirectionTraveled = direction;
    }

    input.UpdateInput();

}

bool IsTimeToMoveSnake()
{
    auto end = std::chrono::high_resolution_clock::now();    
    auto dur = end - lastMove;
    // Check if time to move 
    if(std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() > millisBetweenMoves)
    {
        return true;
    }
    return false;
}

void SnakeDie()
{
    alive = false;
    // Get Death image
    DrawGrid();
    SetSnakeColours();
    
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            deathSave[x][y] = colours[x][y];
        }
    }
}

void MoveSnake()
{
    lastMove = std::chrono::high_resolution_clock::now();

    for(int i = snakeLength - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }
    // Move head of snake (if off screen mirror)
    switch(direction)
    {
        // Up
        case 0:
            snake[0][1] += 1;

            // If off top of screen loop back to bottom
            if(snake[0][1] == 8)
            {
                if(dieOnWall)
                {
                    snake[0][1] -= 1;
                    SnakeDie();
                    return;
                }
                else
                    snake[0][1] = 0;
            }
                
            break;
            // Right
        case 1:
            snake[0][0] += 1;
            if(snake[0][0] == 10)
            {
                if(dieOnWall)
                {
                    snake[0][0] -= 1;
                    SnakeDie();
                    return;
                }
                else 
                    snake[0][0] = 0;
            }
            break;
        case 2:
            snake[0][1] -= 1;
            if(snake[0][1] == -1)
            {
                if(dieOnWall)
                {
                    snake[0][1] += 1;
                    SnakeDie();
                    return;
                }
                else 
                    snake[0][1] = 7;
            }
            break;
        case 3:
            snake[0][0] -= 1;
            if(snake[0][0] == -1)
            {
                if(dieOnWall)
                {
                    snake[0][0] += 1;
                    SnakeDie();
                    return;
                }
                else
                    snake[0][0] = 9;
            }
            break;
    }

    // Check if its hit itself
    for(int i = 1; i < snakeLength; i++)
    {
        if(snake[0] == snake[i])
        {
            SnakeDie();
            return;
        }
    }

    // Check if eaten apple
    if(snake[0] == apple)
    {
        GetNewApplePosition();

        // Add to snake
        snake.push_back(snake[snakeLength - 1]);
        snakeLength++;
        
    }
}

void SnakeInit(bool shouldDieOnWall)
{
    dieOnWall = shouldDieOnWall;
    snake = {{4,3}};
    snakeLength = 1;
    alive = true;
    isDeathSaveShowing = false; 

    // Set Time of start
    lastMove = std::chrono::high_resolution_clock::now();    

    // Get Apple Position
    srand(time(NULL));
    GetNewApplePosition();

    DrawGrid();

    // Set colours based off gridInfo
    SetSnakeColours();

}

void SnakeSelect()
{
    std::vector<int> coords = getCoordsOfMouse();
    if(prevCoords[0] == 0 && coords[0] == 1)
    {
        // Easy Mode Selected
        if(coords[1] < 5)
            SnakeInit(false);
        // Hard Mode Selected
        else
            SnakeInit(true);
        
        programLoaded = true;
        return;
    }

    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            gridInfo[x][y] = '#';
        }
    }

    // Draw 'E'
    gridInfo[1][5] = 'S';
    gridInfo[1][4] = 'S';
    gridInfo[1][3] = 'S';
    gridInfo[1][2] = 'S';
    gridInfo[1][1] = 'S';
    gridInfo[2][5] = 'S';
    gridInfo[3][5] = 'S';
    gridInfo[2][3] = 'S';
    gridInfo[3][3] = 'S';
    gridInfo[2][1] = 'S';
    gridInfo[3][1] = 'S';

    // Draw 'H'
    gridInfo[6][5] = 'A';
    gridInfo[6][4] = 'A';
    gridInfo[6][3] = 'A';
    gridInfo[6][2] = 'A';
    gridInfo[6][1] = 'A';
    gridInfo[7][3] = 'A';
    gridInfo[8][5] = 'A';
    gridInfo[8][4] = 'A';
    gridInfo[8][3] = 'A';
    gridInfo[8][2] = 'A';
    gridInfo[8][1] = 'A';

    SetSnakeColours();
}


void Snake()
{
    if(alive)
    {
        CheckDirection();
        if(IsTimeToMoveSnake())
        {
            MoveSnake();
        }

        DrawGrid();
        SetSnakeColours();
    }
    // I am purposefully not using an else
    if(!alive)
    {
        auto end = std::chrono::high_resolution_clock::now();    
        auto dur = end - lastMove;
        
        // If time to flash screen
        if(std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() > 300)
        {
            lastMove = std::chrono::high_resolution_clock::now(); 

            if(isDeathSaveShowing)
            {
                setAllColours(createRGB(255,255,255));
            }
            else
            {
                for(int x = 0; x < 10; x++)
                {
                    for(int y = 0; y < 8; y++)
                    {
                        colours[x][y] = deathSave[x][y];
                    }
                }
                
            }

            isDeathSaveShowing = !isDeathSaveShowing;
        }

        // Been click
        if(prevCoords[0] == 0 && getCoordsOfMouse()[0] == 1)
        {
            returnToMainMenu();
        }
    }
}