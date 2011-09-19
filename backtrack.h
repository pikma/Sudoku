#ifndef SUDOKU_BACKTRACK_H
#define SUDOKU_BACKTRACK_H

#include "./board.h"

class Backtrack
{
    public:
        Backtrack();
        void explore(Board &b);
        unsigned long getNbCalls() const;
        bool hasFinished() { return _finished; };

    private:
        bool isSolution(const Board &);
        void processSolution(const Board &);
        void getNextMovePosition(Board &, int &index, int *candidates, int &nbCandidates);

        unsigned long _nbCalls;
        bool _finished;
};

#endif
