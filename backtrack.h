#ifndef SUDOKU_BACKTRACK_H
#define SUDOKU_BACKTRACK_H

#include "./board.h"

class Backtrack
{
    public:
        Backtrack();
        void explore(Board &b);
        unsigned long getNbCalls() const;

    private:
        bool isSolution(const Board &);
        void processSolution(const Board &);
        void getNextMovePosition(const Board &, int &index, int *candidates, int &nbCandidates);

        static const int MAX_NB_CANDIDATES = 9;
        unsigned long _nbCalls;
        bool _finished;
};

#endif
