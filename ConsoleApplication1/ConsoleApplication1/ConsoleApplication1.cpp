// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

enum pointState {
  off,
  on,
  dead
};

pointState matrix[3][3] = {
    { off, off, off },
    { off, on,  off },
    { off, off, off }
};


bool is_neighbor_on(int x, int y, int width, int height, pointState ** grid)
{
    return ((x > 0 && grid[x - 1][y] == on)
        || (y > 0 && grid[x][y - 1] == on)
        || (x < width - 1 && grid[x + 1][y] == on)
        || (y < height - 1 && grid[x][y + 1] == on));
}

pointState step_point(int x, int y, int width, int height, pointState ** grid)
{
    pointState current_state = grid[x][y];
    if (current_state == on)
    {
        return dead;
    }
    else if (current_state == dead)
    {
        return off;
    }
    else
    {
        if (is_neighbor_on(x, y, width, height, grid))
        {
            return on;
        }
        else
        {
            return off;
        }
    }
}

pointState ** step_grid( int width, int height, pointState **grid, pointState **out)
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            out[row][column] = step_point(row, column, width, height, grid);
        }
    }

    return out;
}

int main()
{
    std::cout << "Hello World!\n";

    pointState newMatrix[3][3] = {};

    pointState* nM[3];
    pointState* og[3];
    for (int i = 0; i < 3; i++) {
        nM[i] = newMatrix[i];
        og[i] = matrix[i];
    }

    step_grid(3, 3, og, nM);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << newMatrix[i][j] << "\n";
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
