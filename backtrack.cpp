#include "./backtrack.h"
#include <iostream>


const int Backtrack::MAX_NB_CANDIDATES;

Backtrack::Backtrack():
    _nbLeafs(0),
    _nbBranchs(0),
    _finished(false)
{

}

/* The main backtracking method */
void Backtrack::explore(Board &b)
{
    _nbBranchs++;
    // std::cout << "Backtrack::explore(Board &) :: board:\n" << b.toString() << std::endl;
    if (isSolution(b)) {
        processSolution(b);
    }
    else {
        int index, nbCandidates;
        getNextMovePosition(b, index, _candidates, nbCandidates);
        // std::cout << "Position (index) == " << index << ", \n";
        // std::cout << "   candidates = [";
        // for (int i = 0; i < nbCandidates; i++) {
            // if (i != 0)
                // std::cout << ", ";
            // std::cout << _candidates[i];
        // }
        // std::cout << "]\n";

        for (int i = 0; i < nbCandidates; i++) {
            b.applyMove(index, _candidates[i]);
            explore(b);
            b.undoMove(index);
            if (_finished)
                return;
        }
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

long Backtrack::getNbLeafsExplored() const
{
    return _nbLeafs;
}

long Backtrack::getNbBranchs() const
{
    return _nbBranchs;
}

bool Backtrack::isSolution(const Board &b)
{
    _nbLeafs++;
    return b.getFirstEmptyCell() == -1;
}

void Backtrack::processSolution(const Board & b)
{
    std::cout << "Solution found:\n";
    std::cout << b.toString();
    std::cout << std::endl;
    _finished = true;
}
