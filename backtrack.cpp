#include "./backtrack.h"
#include <iostream>


const int Backtrack::MAX_NB_CANDIDATES;

Backtrack::Backtrack():
    _nbCalls(0),
    _finished(false)
{

}

/* The main backtracking method */
void Backtrack::explore(Board &b)
{
    _nbCalls++;
    // std::cout << "Backtrack::explore(Board &) :: board:\n" << b.toString() << std::endl;
    if (isSolution(b)) {
        processSolution(b);
    }
    else {
        int index, nbCandidates;
        int candidates[MAX_NB_CANDIDATES];

        getNextMovePosition(b, index, candidates, nbCandidates);
        // std::cout << "===========================================";
        // std::cout << "Position (index) == " << index << ", \n";
        // std::cout << "   candidates = [";
        // for (int i = 0; i < nbCandidates; i++) {
            // if (i != 0)
                // std::cout << ", ";
            // std::cout << _candidates[i];
        // }
        // std::cout << "]\n";
        // std::cout << b.toString() << std::endl;

        for (int i = 0; i < nbCandidates; i++) {
            b.applyMove(index, candidates[i]);
            explore(b);
            b.undoMove(index);
            if (_finished)
                return;
        }

        // if (nbCandidates == 0 && index > 70) {
            // std::cout << "Leaf position (next index == " << index << "):\n";
            // std::cout << b.toString() << std::endl;
        // }

    }
}

/* Returns the position of the next move, with the candidates for this next move
 */
void Backtrack::getNextMovePosition(const Board &b, int &index,
        int *candidates, int &nbCandidates)
{
    index = b.getFirstEmptyCell();
    b.getCandidates(index, candidates, nbCandidates);
}

unsigned long Backtrack::getNbCalls() const
{
    return _nbCalls;
}

bool Backtrack::isSolution(const Board &b)
{
    return b.getFirstEmptyCell() == -1;
}

void Backtrack::processSolution(const Board & b)
{
    _finished = true;
    std::cout << "Solution found:\n";
    std::cout << b.toString() << std::endl;
    std::cout << "Number of calls to explore(): " << _nbCalls << std::endl;
}
