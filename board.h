/*
 * Author: Pierre Kreitmann
 * pierre.kreitmann [at] gmail [dot] com
 */

#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include <string>

/* This class represents the sudoku problem instance (i.e. a specific sheet of
 * paper with a sudoku on it).
 *
 * There is no checking mechanism to ensure that the sudoku is always correct,
 * but functions are provided to give you the set of legal numbers for any cell.
 *
 * Cells are identified by an index. It is not important how it represents
 * cells: it is returned by getFirstEmptyCell() or getMostConstrainedCell(...),
 * and is used as a parameter by other functions.
 */
class Board {
    public:
        static const int DIMENSION = 9;
        static const int MAX_NB_CANDIDATES = 9;

        // Constructors
        Board();
        Board(const char * filename);
        ~Board();
        Board(const Board &);
        Board& operator=(const Board);

        // Sets a cell of a sudoku to a certain number.
        void applyMove(int index, int number);

        // Erase a cell.
        void undoMove(int index);

        bool isSolution() const;

        /* Returns the cell that has approximately the lowest number of
         * candidates. No guarantee is made that this is actually the one with
         * the lowest number of candidates, it is possible that the cell
         * returned has exactly one candidates while other cells have zero
         * candidates.
         */
        void getMostConstrainedCell(int &index, int *candidates, int
                &nbCandidates); unsigned long getNbGetCandidatesCall();

        /* Returns the first empty cell of the board, or -1 if there is no empty
         * cell.
         */
        int getFirstEmptyCell() const;

        /* Returns the set of numbers that can be put in the cell without
         * conflicting with the rules of the line, the column and the zone.
         */
        void getCandidates(int index, int *candidates, int &nbCandidates);

        // Prints the board
        std::string toString() const;

    private:
        static const int NB_CELLS = DIMENSION * DIMENSION;
        static const int NO_NUMBER = -1;
        int *_numbers;
        unsigned long _nbGetCandidatesCall;

        /* Parses the line and stores it in the _numbers array, starting at the
         * index in argument
         */
        void parseLine(std::string line, int & index);
        // Parses a character and stores it at the index in argument
        void parseChar(char c, int index);

        /* Returns an horizontal line that has the same width as the textual
         * representation of the board (used to delimit zones)
         */
        static std::string horizontalLine();

        // Prints a line of the sudoku
        std::string stringFromLine(int lineIndex) const;


        /* The three methods mark numbers are false in the bool *isCandidate if
         * those numbers appear in the line, the column or the zone of the cell
         * in argument. After value of isCandidate[i] is true if the number i
         * doesn't appear in the line / column / zone.
         *
         * Note: the cell isCandidate[0] is unused, the first possible number
         * is 1.
         */
        void reduceCandidatesByLine(int index, bool *isCandidate);
        void reduceCandidatesByColumn(int index, bool *isCandidate);
        void reduceCandidatesByZone(int index, bool *isCandidate);
};

#endif
