#include "./backtrack.h"
#include <iostream>

Backtrack::Backtrack():
    _nbCalls(0),
    _finished(false)
{
}

// The main backtracking method
void Backtrack::explore(Board &b)
{
    _nbCalls++;
    // std::cout << "Backtrack::explore(Board &) :: board:\n" << b.toString() << std::endl;
    if (isFull(b)) {
        // we assume that the graph given is correct
        processSolution(b);
    }
    else {
        int index, nbCandidates;
        int candidates[Board::MAX_NB_CANDIDATES];

        getNextMovePosition(b, index, candidates, nbCandidates);

        for (int i = 0; i < nbCandidates; i++) {
            b.applyMove(index, candidates[i]);
            explore(b);
            b.undoMove(index);
            if (_finished)
                return;
        }
    }
}

// Returns the position of the next move, with the candidates for this next move
void Backtrack::getNextMovePosition(Board &b, int &index,
        int *candidates, int &nbCandidates)
{
    b.getMostConstrainedCell(index, candidates, nbCandidates);
}

// Returns true if the board doesn't have any empty cell
bool Backtrack::isFull(const Board &b)
{
    return b.getFirstEmptyCell() == -1;
}

// Callback when a solution is found.
void Backtrack::processSolution(const Board & b)
{
    _finished = true;
    std::cout << "Solution found:\n";
    std::cout << b.toString() << std::endl;
}
