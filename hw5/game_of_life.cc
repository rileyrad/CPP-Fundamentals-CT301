#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "game_of_life.h"

using namespace std;

/*game_of_life*/
// Private constructor, used in GenSubGame() to generate a subgame.
// Simply assigns each parameter to their respective member variable, which is what the game looks like.
game_of_life::game_of_life(string window, int height, int width, char live_cell, char dead_cell)
: board_width(width), board_height(height), current_generation(window), current_dead_cell(dead_cell), current_live_cell(live_cell) {}

/*game_of_life*/
// Constructor 1: Reads the file_name and initializes the game.
// The game is initialized by chaining the file_name, default live cell '*', 
// default dead cell '-', and 0 pregenerations into constructor 4.
game_of_life::game_of_life(string file_name) 
: game_of_life(file_name, '*', '-', 0) {}

/*game_of_life*/
// Constructor 2: Reads the file_name and initializes the game with pregenerations.
// The game is initialized by chaining the file_name, default live cell '*', 
// default dead cell '-', and pregenerations (declared by pregens parameter) into constructor 4.
game_of_life::game_of_life(string file_name, int pregens) 
: game_of_life(file_name, '*', '-', pregens) {}

/*game_of_life*/
// Constructor 3: Reads the file_name and initializes the game with live and dead cell characters.
// The game is initialized by chaining the file_name, live_cell parameter, 
// dead_cell parameter, and 0 pregenerations into constructor 4.
game_of_life::game_of_life(string file_name, char live_cell, char dead_cell) 
: game_of_life(file_name, live_cell, dead_cell, 0) {}

/*game_of_life*/
// Constructor 4: Reads the file_name and initializes the game with live and dead cell 
// characters and pregenerations.
// Throws a file not found error and incorrect width and height error. If the file is initialized
// correctly, and the width and height are found, then the board is set by reading the file and putting
// the contents into a 1d string array through a for loop. The live cell and dead cell are set by the parameters,
// then the file is closed and the number of pregenerations are calculated by the pregens parameter.
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

// Private helper methods:

/*SaveGeneration*/
// Uses the game_of_life member struct generation_state to save the current generation, width, height,
// number of calculated generations, live cell, and dead cell. After this information is save in the 
// new_state struct, it is added to the saved_generations_array, with it's index being the amount of 
// saved generations mod 100. The amount of saved generations is then incremented by one.
void game_of_life::SaveGeneration() {
    generation_state new_state;

    new_state.game_board = current_generation;
    new_state.width = board_width;
    new_state.height = board_height;
    new_state.generation = calculated_generations;
    new_state.live = current_live_cell;
    new_state.dead = current_dead_cell;

    saved_generations_array[saved_generations % 100] = new_state;
    saved_generations += 1;
}

/*LoadGeneration*/
// Uses the game_of_life member struct generation_state to load a past generations game board, width, height,
// number of calculated generations, live cell, and dead cell into the current object. The index in the saved
// generations array is the index parameter mod 100.
void game_of_life::LoadGeneration(int index) {
    generation_state old_state = saved_generations_array[index % 100];

    current_generation = old_state.game_board;
    board_width = old_state.width;
    board_height = old_state.height;
    calculated_generations = old_state.generation;
    current_live_cell = old_state.live;
    current_dead_cell = old_state.dead;
}

/*CalculatePercentage*/
// Calculates the percentage of live cells on the board and by storing it within live_cell_counter. Using a for loop
// to search through the string array that is the game board, this variable is incremented within a conditional 
// statement that checks if each index within the string is a live cell. The percentage is then calculate by dividing
// the amount of live cells by the size of the board. I multiply it by 100 for ease of access and to represent and actual
// percentage.
double game_of_life::CalculatePercentage() {
    int live_cell_counter = 0;
    for (int i = 0; i < (board_height * board_width); ++i) {
        if (current_generation[i] == current_live_cell) {
            live_cell_counter += 1;
        }
    }
    return 100 * (static_cast<double>(live_cell_counter) / (board_height * board_width));
}

// HW3 Basic methods:

/*GetGenerations*/
// Returns the number of generations calculated so far.
int game_of_life::GetGenerations() {
    return calculated_generations;
}

/*NextGen*/
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
    SaveGeneration();
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
// Uses a for loop to execute NextGen() n times.
void game_of_life::NextNGen(int n) {
    for (int i = 0; i < n; ++i) {
        NextGen();
    }
}

/*SetLiveCell*/
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

// HW5 Basic methods:

/*GenWindow*/
// Throws an error if the passed height and width are not between 1 and the height and width of the board,
// respectively (domain error). Throws an error if the passed row and col are not between 0 and the height 
// and width of the board minus 1, respectively (range error). Creates a winodw string and populates it with
// the contents of main game, using row and col as a starting point and expanding using the height and width.
// This is done through two for loops to increment the rows and columns. The for loop variables are added to 
// the original parameters and the modulized by the height for row, and the width for col. The final, and used 
// index is calculated by multiplying the previously calculated rowIndex and the boards width. Adding the previously
// calculated colIndex to this will give us the correct index that we need to pull and add to our window string.
// The result is returned.
string game_of_life::GenWindow(int row, int col, int height, int width) {
    if ((height > board_height) || (height < 1) || (width < 1) || (width > board_width)) {
        throw(domain_error("game_of_life - GenWindow(int, int, int, int) - "
                            "Size Out of Bounds for height: " + to_string(height) + ", width: " + to_string(width) + 
                            ", Max values are height: " + to_string(board_height) + ", width: " + to_string(board_width) + ".\n"));
    } else if ((row > board_height - 1) || (row < 0) || (col < 0) || (col > board_width - 1)) {
        throw(range_error("game_of_life - GenWindow(int, int, int, int) - "
                            "Index Out of Bounds for row: " + to_string(row) + ", col: " + to_string(col) + 
                            ", Max values are row: " + to_string(board_height - 1) + ", col: " + to_string(board_width - 1) + ".\n"));
    }
    string window = "";
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            int rowIndex = (row + r) % board_height;
            int colIndex = (col + c) % board_width;
            int index = rowIndex * board_width + colIndex;
            window += current_generation[index];
        }
    }
    return window;
}

/*GenSubGame*/
// Calls GenWindow() using the same parameters to get the desired window of the main game. Creates a new
// game_of_life object by passing in the newly generated window into a private constructor. The window's height,
// width, and the live / dead cells of the main game are also passed through to maintain proper member variables.
game_of_life game_of_life::GenSubGame(int row, int col, int height, int width) {
    string window = GenWindow(row, col, height, width);
    return game_of_life(window, height, width, current_live_cell, current_dead_cell);
}

/*ToggleCell*/
// Throws an error if the index parameter is out of bounds. This means the index is greater than the boards height
// and width multiplied together minus one OR it's less than zero. The error is the inteded range error. If the index
// is valid, then I toggle the cell at the desired location by first checking if it is a dead cell, and changing it 
// to a live one. Otherwise, no additional check is needed because we assume it is a live cell, and it is toggled by
// setting it to a dead one.
void game_of_life::ToggleCell(int index) {
    if ((index > (board_height * board_width) - 1) || (index < 0)) {
        throw(range_error("game_of_life - ToggleCell(int) - "
                            "Index Out of Bounds for index: " + to_string(index) + 
                            ", Max value is index: " + to_string((board_height * board_width) - 1) + ".\n"));
    } else if (current_generation[index] == current_dead_cell) {
        current_generation[index] = current_live_cell;
    } else {
        current_generation[index] = current_dead_cell;
    }
}

/*ToggleCell*/
// Throws a range error if the passed row and col are out of bounds for the board. This means that row and col are
// greater than the height and width minus one, respectively. Or the row and col are less than zero. If the row and col
// are valid, I calculate index by multiplying the row by the width and adding col, and passing that into
// the previous ToggleCell() since they would otherwise have the same implementation (just with two numbers instead).
void game_of_life::ToggleCell(int row, int col) {
    if ((row > board_height - 1) || (row < 0) || (col < 0) || (col > board_width - 1)) {
        throw(range_error("game_of_life - ToggleCell(int, int) - "
                            "Index Out of Bounds for row: " + to_string(row) + ", col: " + to_string(col) +
                            ", Max values are row: " + to_string(board_height - 1) + ", col: " + to_string(board_width - 1) + ".\n"));
    } else {
        ToggleCell(col + (row * board_width));
    }
}

/*IsStillLife*/
// Checks if the game is stuck at standstill by making a temporary copy, incrementing the generation by one,
// then comparing the current game board and the game board of the temporary copy.
bool game_of_life::IsStillLife() {
    game_of_life temp = *this;
    temp.NextGen();
    return current_generation == temp.current_generation;
}

/*GetAvailableGens*/
// Returns the number of safe generations to roll back to. I check if it is above 100 because I don't want to
// return anything larger than 100 since we're only tracking the previous 100 gens. Otherwise I return the
// variable that keeps track of the amount of saved generations.
int game_of_life::GetAvailableGens() {
    if (saved_generations > 100) {
        return 100;
    } else {
        return saved_generations;
    }
}

// Operators:

/*GetAvailableGens*/
// Increments the game by gens. Uses the -= operator and passes in -gens if the passed parameter is negative.
// Otherwise, I incrememnt the game through NextNGen() by passing the gens paramenter into it. Return a referrence
// to the newly incremented object.
game_of_life& game_of_life::operator+=(int gens) {
    if (gens < 0) {
        return *this -= -gens;
    } else {
        NextNGen(gens);
        return *this;
    }
}

/*operator-=*/
// Throws a domain error if the amount of saved generations equals 0. Throws a range error if the passed in parameter
// is greater than 100 or the amount of saved generations. Otherwise, I load the generation I want using my private
// helper method LoadGeneration(), passing in calculated_generations - gens.
game_of_life& game_of_life::operator-=(int gens) {
    if (saved_generations == 0) {
        throw(domain_error("game_of_life - operator-=(int) - No saved generations to roll back to.\n"));
    } else if ((gens > saved_generations) || (gens > 100)) {
        throw(range_error("game_of_life - operator-=(int) - Cannot roll back " + to_string(gens) + " generations. "
                            "Number of saved generations: " + to_string(GetAvailableGens()) + ".\n"));
    } else {
        LoadGeneration(calculated_generations - gens);
        return *this;
    }
}

/*operator+*/
// Checks if the gens parameter is less than zero, if it is, use the - operator using the negative of gens. Otherwise,
// I create a copy of the game and increment the copy gens number of times using NextNGen(). Returns the copy.
game_of_life game_of_life::operator+(int gens) {
    if (gens < 0) {
        return *this - -gens;
    } else {
        game_of_life temp = *this;
        temp.NextNGen(gens);
        return temp;
    }
}

/*operator-*/
// Throws a domain error if the amount of saved generations equals 0. Throws a range error if the passed in parameter
// is greater than 100 or the amount of saved generations. Otherwise, I create a copy of the game and load the wanted 
// previous generation and returning it. The index of the previous generation is calculate by subtracting gens by
// the number of total calculated generations.
game_of_life game_of_life::operator-(int gens) {
    if (saved_generations == 0) {
        throw(domain_error("game_of_life - operator-(int) - No saved generations to roll back to.\n"));
    } else if ((gens > saved_generations) || (gens > 100)) {
        throw(range_error("game_of_life - operator-(int) - Cannot roll back " + to_string(gens) + " generations. "
                            "Number of saved generations: " + to_string(GetAvailableGens()) + ".\n"));
    } else {
        game_of_life temp = *this;
        temp.LoadGeneration(temp.calculated_generations - gens);
        return temp;
    }
}

/*operator--*/
// Simply returns the result of the -= operator using the current object and one.
game_of_life& game_of_life::operator--() {
    return *this -= 1;
}

/*operator--*/
// Simply returns the result of the -= operator using a temporary copy of the current object and one.
game_of_life game_of_life::operator--(int) {
    game_of_life temp = *this;
    *this -= 1;
    return temp;
}

/*operator++*/
// Calls NextGen() to increment the game by one generation, then returns
// result of the game being incremented.
game_of_life& game_of_life::operator++() {
    NextGen();
    return *this;
}

/*operator++*/
// Calls NextGen() to increment the game by one generation, then returns
// what the game_of_life object was BEFORE incrementing, despite it still being incremented.
game_of_life game_of_life::operator++(int fake) {
    game_of_life temp = *this;
    NextGen();
    return temp;
}

/*operator<*/
// Uses my CalculatePercentage() private helper method on the current object and the right hand side.
// Compares these percentages with the normal less than operator.
bool game_of_life::operator<(game_of_life &rhs) {
    return CalculatePercentage() < rhs.CalculatePercentage();
}

/*operator<=*/
// Uses my CalculatePercentage() private helper method on the current object and the right hand side.
// Compares the percentages with the normal less than or equal to operator. Otherwise, I pass the objects
// into the equivalence operator to handle the plus or minus 0.5% equivalence check.
bool game_of_life::operator<=(game_of_life &rhs) {
    if (CalculatePercentage() <= rhs.CalculatePercentage()) {
        return true;
    } else {
        return *this == rhs;
    }
}

/*operator>*/
// Uses my CalculatePercentage() private helper method on the current object and the right hand side.
// Compares these percentages with the normal greater than operator.
bool game_of_life::operator>(game_of_life &rhs) {
    return CalculatePercentage() > rhs.CalculatePercentage();
}

/*operator>=*/
// Uses my CalculatePercentage() private helper method on the current object and the right hand side.
// Compares the percentages with the normal greater than or equal to operator. Otherwise, I pass the objects
// into the equivalence operator to handle the plus or minus 0.5% equivalence check.
bool game_of_life::operator>=(game_of_life &rhs) {
    if (CalculatePercentage() >= rhs.CalculatePercentage()) {
        return true;
    } else {
        return *this == rhs;
    }
}

/*operator==*/
// Uses my CalculatePercentage() private helper method on the current object and the right hand side.
// I calculate the differnce of the two percentages by subtracting the right side percentage by the current
// objects percentage. I check if this difference is within the range of 0.5 and -0.5 since I already multiply
// the percentages by 100 in my private helper methods. If the difference does fall within this range, I return true,
// otherwise false.
bool game_of_life::operator==(game_of_life &rhs) {
    double difference = CalculatePercentage() - rhs.CalculatePercentage();
    if ((difference <= 0.5) && (difference >= -0.5)) {
        return true;
    } else {
        return false;
    }
}

/*operator<<*/
// Populates the output stream, os, with a formatted generation. 
// Formatted generation: Defines and populates a string with number of generations calculate.
// Uses two for loops to populate the string with the entire game board which
// is stored in current_generation.
ostream & operator<<(ostream &os, const game_of_life &game) {
    string output = "";
    output += "Generation: " + to_string(game.calculated_generations) + "\n";
    for (int row = 0; row < game.board_height; ++row) {
        for (int col = 0; col < game.board_width; ++col) {
            output += game.current_generation[row * game.board_width + col];
        }
        output += "\n";
    }
    output += "\n";
    return os << output;
}