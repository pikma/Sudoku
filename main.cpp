#include "./board.h"
#include "./backtrack.h"
#include <iostream>

int main(int argc, char ** argv)
{
    Board b("easySudoku.txt");
    std::cout << "Initial configuration:\n" << b.toString() << std::endl;
    Backtrack backtrack;
    backtrack.explore(b);
    std::cout << "Nb leafs explored: " << backtrack.getNbLeafsExplored() << std::endl;
    std::cout << "Nb branchs: " << backtrack.getNbBranchs() << std::endl;
}
