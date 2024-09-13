#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <string>
#include <iostream>
#include <array>

class game_of_life {
	// Insert Data Member Variables here
    int calculated_generations = 0;
    int board_width;
    int board_height;

    std::string current_generation;
    std::string next_generation;

    char current_dead_cell = '-';
    char current_live_cell = '*';

    struct generation_state {
        std::string game_board;
        int width;
        int height;
        int generation;
        char live;
        char dead;
    };

    int saved_generations = 0;
    std::array <generation_state, 100> saved_generations_array;
	
    // Invalid read and FNF error need to include the offending file name and be closed off by the error end string
	constexpr static const char * cell_dupe_error = "game_of_life - Live Cell and Dead Cell cannot be the same character\n";
	constexpr static const char * file_not_found_error = "game_of_life - File Not Found \"";
	constexpr static const char * invalid_read_error = "game_of_life - Width and Height incorrectly formatted for file \"";
	constexpr static const char * error_end = "\"\n";
	
    // Private helper methods:

    /*SaveGeneration*/
    // Input: None
    // Output: None
    void SaveGeneration();

    /*LoadGeneration*/
    // Input: index (int)
    // Output: None
    void LoadGeneration(int index);

    /*CalculatePercentage*/
    // Input: None
    // Output: Percentage of live cells in the current generation (double)
    double CalculatePercentage();

    /*game_of_life*/
    // Input: window (string), height (int), width (int), live_cell (char), dead_cell (char)
    // Output: A game_of_life object that is constructed from the contents of window, height, 
    // width, live_cell, and dead_cell.
    game_of_life(std::string window, int height, int width, char live_cell, char dead_cell);

public:

    // All Constructors throw runtime errors , File not Found, Invalid Width and Height, Live and Dead Cell duplication
    game_of_life() = delete;

    /*game_of_life*/
    // Input: file_name (string)
    // Output: A game_of_life object that is constructed from the contents of file_name, default live cell '*', 
    // default dead cell '-', and 0 pregenerations.
    game_of_life(std::string file_name);

    /*game_of_life*/
    // Input: file_name (string), pregens (int)
    // Output: A game_of_life object that is constructed from the contents of file_name, default live cell '*', 
    // default dead cell '-', and a number of pregenerations declared by the "pregens" parameter.
    game_of_life(std::string file_name, int pregens);

    /*game_of_life*/
    // Input: file_name (string), live_cell (char), dead_cell (char)
    // Output: A game_of_life object that is constructed from the contents of file_name, live_cell, 
    // dead_cell, and 0 pregenerations.
    game_of_life(std::string file_name, char live_cell, char dead_cell);

    /*game_of_life*/
    // Input: file_name (string), live_cell (char), dead_cell (char), pregens (int)
    // Output: A game_of_life object that is constructed from the contents of file_name, live_cell, 
    // dead_cell, and a number of pregenerations declared by the "pregens" parameter.
    game_of_life(std::string file_name, char live_cell, char dead_cell, int pregens);

    // Defaults for Destructor, Copy Constructor, Assignment Operator, 
    // Move Operator, Move Assignment Operator:
    game_of_life(const game_of_life &rhs) = default;
    game_of_life &operator=(const game_of_life &rhs) = default;
    game_of_life &operator=(game_of_life &&rhs) = default;
    game_of_life(game_of_life &&rhs) = default;
    virtual ~game_of_life() = default;

    // HW3 Basic Methods:

    /*GetGenerations*/
    // Input: None
    // Output: The number of previously calculated generations (int)
    int GetGenerations();
    
    /*NextGen*/
    // Input: None
    // Output: None
    void NextGen();

    /*NextNGen*/
    // Input: Number of generations to calculate, n (int)
    // Output: None
    void NextNGen(int n);

    /*SetLiveCell*/
    // Input: The new live cell for the game, live_cell (char)
    // Output: None
    void SetLiveCell(char live_cell);

    /*SetDeadCell*/
    // Input: The new dead cell for the game, dead_cell (char)
    // Output: None
    void SetDeadCell(char dead_cell);

    // HW5 Basic Methods:

    /*GenWindow*/
    // Input: row (int), col (int), height (int), width (int)
    // Output: A window of the game, starting at index: row, col (string)
    std::string GenWindow(int row, int col, int height, int width);

    /*GenSubGame*/
    // Input: row (int), col (int), height (int), width (int)
    // Output: A new game_of_life object that is a subgame of the game it is called within
    game_of_life GenSubGame(int row, int col, int height, int width);

    
    /*ToggleCell*/
    // Input: index of the cell to toggle (int)
    // Output: None
    void ToggleCell(int index);

    /*ToggleCell*/
    // Input: index of the cell to toggle, in the form of the row (int), and column (int)
    // Output: None
    void ToggleCell(int row, int col);

    /*IsStillLife*/
    // Input: None
    // Output: Boolean indicating whether the current generation is a still life configuration.
    bool IsStillLife();

    /*GetAvailableGens*/
    // Input: None
    // Output: Number of available saved generations (int)
    int GetAvailableGens();

    // Operators:

    /*operator+=*/
    // Input: Number of generations to increment (int)
    // Output: Reference to the incremented game_of_life object
    game_of_life& operator+=(int gens);

    /*operator-=*/
    // Input: Number of generations to decrement (int)
    // Output: Reference to the decremented game_of_life object
    game_of_life& operator-=(int gens);

    /*operator+*/
    // Input: Number of generations to increment (int)
    // Output: Reference to the incremented game_of_life object
    game_of_life operator+(int gens);

    /*operator-*/
    // Input: Number of generations to decrement (int)
    // Output: Reference to the decremented game_of_life object
    game_of_life operator-(int gens);

    /*operator--*/
    // Input: None
    // Output: Reference to the game_of_life object, decremented by 1
    game_of_life& operator--();

    /*operator--*/
    // Input: fake (int)
    // Output: Reference to the game_of_life object, decremented by 1
    game_of_life operator--(int);

    /*operator++*/
    // Input: None
    // Output: Reference to the game_of_life object, incremented by 1
    game_of_life& operator++();

    /*operator++*/
    // Input: fake (int)
    // Output: Reference to the game_of_life object, incremented by 1
    game_of_life operator++(int fake);
    
    /*operator<*/
    // Input: rhs (game_of_life&)
    // Output: Boolean indicating whether the current game has a lower percentage of live cells.
    bool operator<(game_of_life &);

    /*operator<=*/
    // Input: rhs (game_of_life&)
    // Output: Boolean indicating whether the current game has a lower or equal percentage of live cells.
    bool operator<=(game_of_life &);

    /*operator>*/
    // Input: rhs (game_of_life&)
    // Output: Boolean indicating whether the current game has a higher percentage of live cells.
    bool operator>(game_of_life &);

    /*operator>=*/
    // Input: rhs (game_of_life&)
    // Output: Boolean indicating whether the current game has a higher or equal percentage of live cells.
    bool operator>=(game_of_life &);

    /*operator==*/
    // Input: rhs (game_of_life&)
    // Output: Boolean indicating whether the current game has approximately (plus or minus 0.5%) equal 
    // percentage of live cells.
    bool operator==(game_of_life &);

    /*operator<<*/
    // Input: os (ostream), game (const game_of_life&)
    // Output: An ostream populated with the formatted game board and generation information.
    friend std::ostream & operator<<(std::ostream &os, const game_of_life &game);
};
#endif