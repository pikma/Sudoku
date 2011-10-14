#ifndef SUDOKU_BACKTRACK_H
#define SUDOKU_BACKTRACK_H

#include "./board.h"

class Backtrack
{
    public:
        Backtrack();

        /* This method tries to find solution of the board given in argument.
         * After its execution, you can test wether the board has a solution or
         * not with hasSolution().
         *
         * There is no guarantee if the board b doesn't respect the rules of the
         * sudoku (e.g. if the board b already has two 1 in the same line).
         */
        void explore(Board &b);

        /* Returns true iff the board given to explore(...) has a solution.
         * If this board doesn't admit any solution, returns false.
         */
        bool hasSolution() const { return _finished; };

        /* Returns the number of calls to the recursive explore(...) method.
         * This provides an indication of the performance of the algorithm.
         */
        unsigned long getNbCalls() const { return _nbCalls; };

    private:
        // Returns true if a board doesn't have any empty cell.
        bool isFull(const Board &);

        // This function is executed on the first solution found.
        void processSolution(const Board &);

        // Returns the position of the next move, with the candidates for this next move
        void getNextMovePosition(Board &b, int &index, int *candidates, int &nbCandidates);

        unsigned long _nbCalls;
        bool _finished;
};

#endif
