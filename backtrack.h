#ifndef SUDOKU_BACKTRACK_H
#define SUDOKU_BACKTRACK_H

#include "./board.h"

class Backtrack
{
    public:
        Backtrack();
        void explore(Board &b);
        long getNbLeafsExplored() const;
        long getNbBranchs() const;

    private:
        bool isSolution(const Board &);
        void processSolution(const Board &);
        void getNextMovePosition(const Board &, int &index, int *candidates, int &nbCandidates);

        bool _finished;
        static const int MAX_NB_CANDIDATES = 9;
        int _candidates[MAX_NB_CANDIDATES];
        long _nbLeafs;
        long _nbBranchs;
};

#endif
