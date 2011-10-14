#include "./board.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

const int Board::DIMENSION;
const int Board::NB_CELLS;
const int Board::NO_NUMBER;
const int Board::MAX_NB_CANDIDATES;

////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////

Board::Board():
    _nbGetCandidatesCall(0)
{
    _numbers = new int[NB_CELLS];
    for (int i = 0; i < NB_CELLS; i++) {
        _numbers[i] = NO_NUMBER;
    }
}

Board::~Board()
{
    delete[] _numbers;
}

Board::Board(const char * filename):
    _nbGetCandidatesCall(0)
{
    _numbers = new int[NB_CELLS];

    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string line;
        int index = 0;
        while (inputFile.good()) {
            std::getline(inputFile, line);
            parseLine(line, index);
        }
        inputFile.close();
    }
    else {
        std::cerr << "Error: can't open file " << filename;
        exit(EXIT_FAILURE);
    }

}

Board::Board(const Board & b):
    _nbGetCandidatesCall(b._nbGetCandidatesCall)
{
    _numbers = new int[NB_CELLS];
    for (int i = 0; i < NB_CELLS; i++) {
        _numbers[i] = b._numbers[i];
    }
}

Board& Board::operator=(const Board b)
{
    for (int i = 0; i < NB_CELLS; i++) {
        _numbers[i] = b._numbers[i];
    }
    return *this;
}

void
Board::parseLine(std::string line, int & index)
{
    unsigned int i = 0;
    while (i < line.length()) {
        char c = line.at(i);
        parseChar(c, index);
        index++;
        i++;

        // discard the whitespaces
        while (i < line.length() && (line.at(i) == ' '))
            i++;
    }

    // Error checking
    if (index % DIMENSION != 0) {
        std::cerr << "Error in input file, line:\n";
        std::cerr << "   " << line << "\n";
        std::cerr << "Index = " << index << ", should be a multiple of " << DIMENSION << "\n";
        exit(EXIT_FAILURE);
    }
}

void
Board::parseChar(char c, int index)
{
    if (c == '#') {
        _numbers[index] = NO_NUMBER;
    }
    else {
        int number = c - '0';
        _numbers[index] = number;
    }
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods
////////////////////////////////////////////////////////////////////////////////

std::string Board::toString() const
{
    std::string result = "";
    for (int i = 0; i < DIMENSION; i++) {
        if (i % 3 == 0) // zone delimiter
            result += Board::horizontalLine();

        result += stringFromLine(i);
    }

    result += Board::horizontalLine(); // the last line
    return result;
}

std::string
Board::stringFromLine(int lineIndex) const
{
    std::string result;
    for (int j = 0; j < DIMENSION; j++) {
        if (j % 3 == 0) // zone delimiter
            result += "| ";
        int index = lineIndex * DIMENSION + j;
        if (_numbers[index] == NO_NUMBER) {
            result += " ";
        }
        else {
            result += '0' + _numbers[index];
        }
        result +=  " ";
    }
    result += "|\n";
    return result;
}

std::string
Board::horizontalLine() {
    std::string result;
    for (int j = 0; j < 25; j++) {
        result += "-";
    }
    result += "\n";

    return result;
}

void
Board::applyMove(int index, int number)
{
    _numbers[index] = number;
}

void
Board::undoMove(int index)
{
    _numbers[index] = NO_NUMBER;
}

int
Board::getFirstEmptyCell() const
{
    for (int i = 0; i < NB_CELLS; i++) {
        if (_numbers[i] == NO_NUMBER)
            return i;
    }
    return -1;
}

void
Board::getCandidates(int index, int *candidates, int &nbCandidates)
{
    _nbGetCandidatesCall++;
    bool isCandidate[DIMENSION+1]; // we ignore the [0] cell, numbers are from 1 to 9
    for (int i = 1; i <= DIMENSION; i++)
        isCandidate[i] = true;

    // Reduce the set of candidates
    reduceCandidatesByLine(index, isCandidate);
    reduceCandidatesByColumn(index, isCandidate);
    reduceCandidatesByZone(index, isCandidate);


    // Copy the result in the arguments
    nbCandidates = 0;
    for (int i = 1; i <= DIMENSION; i++) {
        if (isCandidate[i]) {
            candidates[nbCandidates] = i;
            nbCandidates++;
        }
    }
}

void
Board::reduceCandidatesByLine(int index, bool *isCandidate)
{
    int firstOfLine = index - (index % DIMENSION);
    for (int i = firstOfLine; i < firstOfLine + DIMENSION; i++) {
        int number = _numbers[i];
        if (number != NO_NUMBER)
            isCandidate[number] = false;
    }
}

void
Board::reduceCandidatesByColumn(int index, bool *isCandidate)
{
    // Column
    int firstOfCol = index % 9;
    for (int i = firstOfCol; i < NB_CELLS; i += DIMENSION) {
        int number = _numbers[i];
        if (number != NO_NUMBER)
            isCandidate[number] = false;
    }
}

void
Board::reduceCandidatesByZone(int index, bool *isCandidate)
{
    int colIx = index % 9;
    int lineIx = index / 9;
    int zoneFirstColIx = colIx - (colIx % 3);
    int zoneFirstLineIx = lineIx - (lineIx % 3);
    int firstCell = DIMENSION * zoneFirstLineIx + zoneFirstColIx;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int number = _numbers[firstCell + j];
            if (number != NO_NUMBER)
                isCandidate[number] = false;
        }
        firstCell += DIMENSION;
    }
}

bool
Board::isSolution() const
{
    for (int i = 0; i < NB_CELLS; i++) {
        if (_numbers[i] == NO_NUMBER)
            return false;
    }
    return true;
}

void
Board::getMostConstrainedCell(int &index, int *candidates,
        int &nbCandidates)
{
    // we store the result of getCandidates into two temporary variables
    int currentCandidates[MAX_NB_CANDIDATES];
    int currentNbCandidates;

    nbCandidates = MAX_NB_CANDIDATES + 1; // this will be the minimum
    index = -1; // in case all the cells are filled

    for (int i = 0; i < NB_CELLS; i++) {
        if (_numbers[i] != NO_NUMBER)
            continue;

        getCandidates(i, currentCandidates, currentNbCandidates);

        if (currentNbCandidates < nbCandidates) {
            nbCandidates = currentNbCandidates;
            index = i;
            for (int j = 0; j < MAX_NB_CANDIDATES; j++) {
                candidates[j] = currentCandidates[j];
            }
        }

        if (nbCandidates <= 1)
            return;
        /* Here, we could put (nbCandidates == 0) instead. It proves to make
         * about twice as many calls to getCandidates() on the hardest sudoku.
         */
    }
}

unsigned long
Board::getNbGetCandidatesCall()
{
    return _nbGetCandidatesCall;
}
