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

    if (!backtrack.hasFinished()) {
        std::cout << "There is no solution." << std::endl;
    }
    std::cout << "Nb calls to explore(): " << backtrack.getNbCalls();
    std::cout << std::endl;
    std::cout << "Nb calls to getCandidates(): " << b.getNbGetCandidatesCall();
    std::cout << std::endl;
}

