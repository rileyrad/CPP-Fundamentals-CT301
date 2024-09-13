#include "game_of_life.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[])
{
    game_of_life A(argv[1]);


    cout << A << endl;
    A = A + 1;
    cout << A << endl;
    ++A;
    cout << A << endl;
    A.NextGen();
    cout << A << endl;
    A.NextNGen(100);
    cout << A << endl;

    return 0;
}