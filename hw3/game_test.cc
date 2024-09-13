#include "game_of_life.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    game_of_life game(argv[1]);
    cout << game;
    game.NextGen();
    cout << game;
    game.NextGen();
    cout << game;
    game.NextGen();
    cout << game;
    game.NextGen();
    cout << game;
    game.NextGen();
    cout << game;
    return 0;
}