#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "game_of_life.h"

using namespace std;

// Constructor 1: Reads the filename and initializes the game.
game_of_life::game_of_life(string file_name) 
: game_of_life(file_name, '*', '-', 0) {}

// Constructor 2: Reads the filename and initializes the game with pregenerations.
game_of_life::game_of_life(string file_name, int pregens) 
: game_of_life(file_name, '*', '-', pregens) {}

// Constructor 3: Reads the filename and initializes the game with live and dead cell characters.
game_of_life::game_of_life(string file_name, char live_cell, char dead_cell) 
: game_of_life(file_name, live_cell, dead_cell, 0) {}

// Constructor 4: Reads the filename and initializes the game with live and dead cell 
// characters and pregenerations.
game_of_life::game_of_life(string file_name, char live_cell, char dead_cell, int pregens) {
    // File not found error.
    ifstream file(file_name);
    if (!file.is_open()) {
        throw(runtime_error(file_not_found_error + file_name + error_end));
    }

    // Incorrect width height format.
    string line;
    getline(file, line);
    istringstream ss(line);
    ss >> board_width >> board_height;
    if (ss.fail()) {
        throw(runtime_error(invalid_read_error + file_name + error_end));
    }

    if (board_width <= 0 || board_height <= 0) {
        throw(runtime_error(invalid_read_error + file_name + error_end));
    }

    // Establish the board.
    current_generation = string(board_width * board_height, dead_cell);
    next_generation = string(board_width * board_height, dead_cell);
    getline(file, line);
    int col;
    for (int i = 0; file && i < (board_height * board_width); ++i) {
        col = i % board_width;
        current_generation[i] = line[col];
        if (col == board_width - 1) {
            getline(file, line);
        }
    }
    SetLiveCell(live_cell);
    SetDeadCell(dead_cell);

    file.close();

    // Calculate the number of pregenerations.
    NextNGen(pregens);
}

/*GetGenerations*/
// Input: None
// Output: Grabs the int variable calculated_generations
// calculated_generations is used to track the amount of generations that has been calculated.
int game_of_life::GetGenerations() {
    return calculated_generations;
}

/*NextGen*/
//Input: None
//Output: None
// Used the game of life rules.
// The first two for loops are used to keep track of the rows and 
// columns, which are used to find each individual cell.
// An integer variable and two more for loops are used to calculate the
// number of live neighbors around the specified cell.
// After calculating the live neighbors, a series of conditional statements
// is used to determine whether or not the cell should be a dead cell or a live cell.
// At the very end, the current generation is updated using the generation that was
// manipulated in the method, and the number of calculated generations is incremented by 1.
void game_of_life::NextGen() {
    for (int row = 0; row < board_height; ++row) {
        for (int col = 0; col < board_width; ++col) {
            // Calculate neighbors
            int live_neighbors = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) continue;
                    int neighbor_row = (row + i + board_height) % board_height;
                    int neighbor_col = (col + j + board_width) % board_width;
                    if (neighbor_row < 0 || neighbor_row >= board_height || neighbor_col < 0 || neighbor_col >= board_width) {
                        continue;
                    }
                    if (current_generation[neighbor_row * board_width + neighbor_col] == current_live_cell) {
                        ++live_neighbors;
                    }
                }
            }

            int cell = row * board_width + col;
            if (current_generation[cell] == current_live_cell && (live_neighbors == 2 || live_neighbors == 3)) {
                next_generation[cell] = current_live_cell;
            } else if (current_generation[cell] == current_dead_cell && live_neighbors == 3) {
                next_generation[cell] = current_live_cell;
            } else {
                next_generation[cell] = current_dead_cell;
            }
        }
    }
    current_generation = next_generation;
    calculated_generations += 1;
}

/*NextNGen*/
// Input: An integer, n, that specifies the amount of generations to calculate.
// Output: None
// Uses a for loop to execute NextGen() n times.
void game_of_life::NextNGen(int n) {
    for (int i = 0; i < n; ++i) {
        NextGen();
    }
}

/*SetLiveCell*/
// Input: The character that will represent live cells on the board.
// Output: None
// First, throws an error if the passed live cell is the same as the current dead cell. 
// Second, replaces every instance of the old live cell to the new live cell. 
// Third, uses the 'this' keyword to set the live cell that is now used on the board 
// to the character specified by the user.
void game_of_life::SetLiveCell(char live_cell) {
    if (live_cell == current_dead_cell) {
        throw(runtime_error(cell_dupe_error));
    } else {
        for (int i = 0; i < (board_height * board_width); ++i) {
            if (current_generation[i] == current_live_cell) {
                current_generation[i] = live_cell;
            }
        }
        this->current_live_cell = live_cell;
    }
}

/*SetDeadCell*/
// Input: The character that will represent dead cells on the board.
// Output: None
// First, throws an error if the passed dead cell is the same as the current live cell. 
// Second, replaces every instance of the old dead cell to the new dead cell. 
// Third, uses the 'this' keyword to set the dead cell that is now used on the board 
// to the character specified by the user.
void game_of_life::SetDeadCell(char dead_cell) {
    if (dead_cell == current_live_cell) {
        throw(runtime_error(cell_dupe_error));
    } else {
        for (int i = 0; i < (board_height * board_width); ++i) {
            if (current_generation[i] == current_dead_cell) {
                current_generation[i] = dead_cell;
            }
        }
        this->current_dead_cell = dead_cell;
    }
}

/*operator+*/
// Input: The integer, gens, represents the number of generations to increment to.
// Output: The game_of_life object that is being manipulated.
// Calls NextNGen(), passing gens as n, the number of generations to calculate.
game_of_life& game_of_life::operator+(int gens) {
    NextNGen(gens);
    return *this;
}

/*operator++*/
// Input: None
// Output: The game_of_life object that is being manipulated.
// The pre-increment operator:
// Calls NextGen() to increment the game by one generation, then returns
// result of the game being incremented.
game_of_life& game_of_life::operator++() {
    NextGen();
    return *this;
}

/*operator++*/
// Input: An integer, fake. I have no idea what this is supposed to be used for as I didn't see a need for it.
// Output: The game_of_life object that is being manipulated.
// The pose-increment operator:
// Calls NextGen() to increment the game by one generation, then returns
// what the game_of_life object was BEFORE incrementing, despite it still being incremented.
game_of_life game_of_life::operator++(int fake) {
    game_of_life temp = *this;
    NextGen();
    return temp;
}

/*ToString*/
// Input: None
// Output: The formatted string of a generation count and game board.
// Defines and populates a string with number of generations calculate.
// Uses two for loops to populate the string with the entire game board which
// is stored in current_generation.
string game_of_life::ToString() const {
    string output = "";
    output += "Generation: " + to_string(calculated_generations) + "\n";
    for (int row = 0; row < board_height; ++row) {
        for (int col = 0; col < board_width; ++col) {
            output += current_generation[row * board_width + col];
        }
        output += "\n";
    }
    output += "\n";
    return output;
}

/*operator<<*/
// Input: An output stream and the game_of_life object.
// Output: The output stream populated with the game board and game generations.
// Populates the output stream, os, with the game.ToString(), the formatted generation.
ostream & operator<<(ostream &os, const game_of_life &game) {
    return os << game.ToString();
}