#include <iostream>
#include <vector>
#include <random>

const int ROWS = 30; // number of rows in the grid
const int COLS = 30; // number of columns in the grid
const int STEPS = 10; // number of steps to run the simulation
const int NUM_STATES = 2; // number of possible states for a cell (e.g. alive/dead)

// 2D grid of cells
std::vector<std::vector<int>> grid(ROWS, std::vector<int>(COLS));

int main()
{
    // initialize the grid with random states
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, NUM_STATES - 1);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = distribution(generator);
        }
    }

    // run the simulation
    for (int step = 0; step < STEPS; step++) {
        // create a new grid to store the next state
        std::vector<std::vector<int>> next_grid(ROWS, std::vector<int>(COLS));

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                // count the number of alive neighbors
                int alive_neighbors = 0;
                for (int ii = i - 1; ii <= i + 1; ii++) {
                    for (int jj = j - 1; jj <= j + 1; jj++) {
                        if (ii >= 0 && ii < ROWS && jj >= 0 && jj < COLS && !(ii == i && jj == j)) {
                            if (grid[ii][jj] == 1) {
                                alive_neighbors++;
                            }
                        }
                    }
                }

                // apply the rules of the automata
                if (grid[i][j] == 1) {
                    if (alive_neighbors < 2 || alive_neighbors > 3) {
                        next_grid[i][j] = 0;
                    } else {
                        next_grid[i][j] = 1;
                    }
                } else {
                    if (alive_neighbors == 3) {
                        next_grid[i][j] = 1;
                    } else {
                        next_grid[i][j] = 0;
                    }
                }
            }
        }

        // update the grid
        grid = next_grid;
    }

    // print the final state of the grid
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
