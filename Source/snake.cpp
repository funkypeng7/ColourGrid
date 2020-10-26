#include "global.h"
#include "functions.h"
#include "snake.h"
#include "touchSensor.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>

// Time between snake moves in milliseconds
const int millisBetweenMoves = 1000;

std::vector<std::vector<int>> snake = {{4, 3}, {3, 3}, {2, 3}, {2, 2}, {2, 1}};

int lengthOfSnake = 5;
std::vector<int> apple;

std::vector<float> startPress;

// Time Of Last Movement
auto lastMove = std::chrono::high_resolution_clock::now();    

// 0 - up, 1 - right, 2 - down, 3 - left
int direction = 0;
int lastDirectionTraveled = 0;

// Grid info
// '#' - Empty (white)
// 'S' - Snake (green)
// 'H' - Head of Snake (darker green)
// 'A' - Apple (red)

void GetNewApplePosition()
{
    apple = {rand() % 10 + 1, rand() % 8 + 1};
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
    for(int i = 1; i < lengthOfSnake; i++)
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
    std::vector<float> vec = getRawCoordsOfMouse();
    // First Press
    if(prevRawCoords[0] == 0 && vec[0] == 1)
    {
        startPress = vec;
        std::cout << "Start Press Set\n";
    }
    // Letting go
    if(prevRawCoords[0] == 1 && vec[0] == 0)
    {
        std::vector<float> deltaVector = {prevRawCoords[1] - startPress[1], prevRawCoords[2] - startPress[2]};
        // std::cout << "vec" << vec[0] << ", " << vec[1] << ", " << vec[2] << "\n";
        // std::cout << "start press" << startPress[0] << ", " << startPress[1] << ", " << startPress[2] << "\n";
        std::cout << "Delta Vector" << deltaVector[0] << ", " << deltaVector[1] << "\n";

        // Up
        if(deltaVector[1] > 100 && (lastDirectionTraveled != 2 || lengthOfSnake == 1))
            direction = 0;
        // Right
        else if(deltaVector[0] > 100 && (lastDirectionTraveled != 3 || lengthOfSnake == 1))
            direction = 1;
        // Down
        else if(deltaVector[1] < -100 && (lastDirectionTraveled != 0 || lengthOfSnake == 1))
            direction = 2;
        // Left
        else if(deltaVector[0] < -100 && (lastDirectionTraveled != 1 || lengthOfSnake == 1))
            direction = 3;

        lastDirectionTraveled = direction;
    }

    prevRawCoords = vec;

}

bool IsTimeToMoveSnake()
{
    auto end = std::chrono::high_resolution_clock::now();    
    auto dur = end - lastMove;
    // Check if time to move 
    // std::cout << "time since last move " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << '\n';
    if(std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() > millisBetweenMoves)
    {
        return true;
    }
    return false;
}

void MoveSnake()
{
    lastMove = std::chrono::high_resolution_clock::now();

    for(int i = lengthOfSnake - 1; i > 0; i--)
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
                snake[0][1] = 0;
            break;
            // Right
        case 1:
            snake[0][0] += 1;
            if(snake[0][0] == 10)
                snake[0][0] = 0;
            break;
        case 2:
            snake[0][1] -= 1;
            if(snake[0][1] == -1)
                snake[0][1] = 7;
            break;
        case 3:
            snake[0][0] -= 1;
            if(snake[0][0] == -1)
                snake[0][0] = 9;
            break;
    }

    // 

}

void SnakeInit()
{
    // Set Time of start
    lastMove = std::chrono::high_resolution_clock::now();    

    // Get Apple Position
    srand(time(NULL));
    GetNewApplePosition();

    DrawGrid();

    // Set colours based off gridInfo
    SetSnakeColours();

}

void Snake()
{
    CheckDirection();
    if(IsTimeToMoveSnake())
    {
        MoveSnake();
    }

    DrawGrid();
    SetSnakeColours();

}