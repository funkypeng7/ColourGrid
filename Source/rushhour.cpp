#include <iostream>
#include <fstream>

#define WALL 0;
#define EXIT 1;

void RushhourInit(char gridInfo[10][8])
{
    int i, j;

    for(i = 1; i < 9; i++) {
        for(j= 0; j < 7; j++) {
            gridInfo[i][j] = WALL;
        }
    }

    gridInfo[8][3] = EXIT;
}

void AddCars()
{
    std::ifstream b_file ( "example.txt" );



}

void Rushhour()
{

}