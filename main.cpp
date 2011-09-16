#include "./board.h"
#include "./backtrack.h"
#include <iostream>

int main(int argc, char ** argv)
{
    const char * filename = NULL;
    if (argc < 2) {
        filename = "easySudoku.txt";
    }
    else {
        filename = argv[1];
    }
    Board b(filename);
    std::cout << "Initial configuration:\n" << b.toString() << std::endl;
    Backtrack backtrack;
    backtrack.explore(b);
}
