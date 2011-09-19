#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include <string>

class Board
{
	public:
        static const int DIMENSION = 9;
		Board();
        Board(const char * filename);
        ~Board();
        Board(const Board &);
        Board& operator=(const Board);

        void applyMove(int index, int number);
        void undoMove(int index);
        bool isSolution() const;
        void getMostConstrainedCell(int &index, int *candidates, int &nbCandidates);
        unsigned long getNbGetCandidatesCall();

        /* Returns the first empty cell of the board, or -1 if there is no empty
         * cell.
         */
        int getFirstEmptyCell() const;
        void getCandidates(int index, int *candidates, int &nbCandidates);
        std::string toString() const;

        static const int MAX_NB_CANDIDATES = 9;
	private:
        static const int NB_CELLS = DIMENSION * DIMENSION;
        static const int NO_NUMBER = -1;
        int *_numbers;
        unsigned long _nbGetCandidatesCall;
        // int indexFromCoord(int x, int y);
        // void coordFromIndex(int index, int &x, int &y);
};

#endif
