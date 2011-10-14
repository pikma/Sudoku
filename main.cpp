#include "./board.h"
#include "./backtrack.h"
#include <iostream>

int main(int argc, char ** argv)
{
    const char * filename = NULL;
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " fileName" << std::endl << std::endl ;
        std::cout << "For examples or sudoku files, look at:" << std::endl;
        std::cout << "easySudoku.txt - a very easy Sudoku" << std::endl;
        std::cout << "leMondeSudoku.txt - a sudoku from the daily newspaper Le Monde, supposedly hard" << std::endl;
        std::cout << "sudokuHardest.txt - the hardest sudoku known to have a unique solution (try it ;) )" << std::endl;

        filename = "easySudoku.txt";
        std::cout << std::endl;
        std::cout << "By default, I'll use easySudoku.txt" << std::endl << std::endl;
    }
    else {
        filename = argv[1];
    }
    Board b(filename);
    std::cout << "Initial board:\n" << b.toString() << std::endl;
    Backtrack backtrack;
    backtrack.explore(b);

    if (!backtrack.hasSolution()) {
        std::cout << "There is no solution." << std::endl;
    }
    std::cout << "Nb calls to explore(): " << backtrack.getNbCalls();
    std::cout << std::endl;
    std::cout << "Nb calls to getCandidates(): " << b.getNbGetCandidatesCall();
    std::cout << std::endl;
}

