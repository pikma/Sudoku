#include "./board.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

const int Board::DIMENSION;
const int Board::NB_CELLS;
const int Board::NO_NUMBER;

Board::Board()
{
    _numbers = new int[NB_CELLS];
}

Board::~Board()
{
    delete[] _numbers;
}

Board::Board(const char * filename)
{
    _numbers = new int[NB_CELLS];

    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string line;
        int index = 0;
        while (inputFile.good()) {
            std::getline(inputFile, line);
            unsigned int i = 0;
            while (i < line.length()) {
                char c = line.at(i);
                if (c == '#') {
                    _numbers[index] = -1;
                }
                else {
                    int number = c - '0';
                    _numbers[index] = number;
                }
                index++;

                i++;

                while (i < line.length() && (line.at(i) == ' ' || line.at(i) == '\n'))
                    i++;

            }
            if (index % DIMENSION != 0) {
                std::cerr << "Error in input file, line:\n";
                std::cerr << "   " << line << "\n";
                std::cerr << "Index = " << index << ", should be a multiple of " << DIMENSION << "\n";
                exit(EXIT_FAILURE);
            }
        }
        inputFile.close();
    }
    else {
        std::cerr << "Error: can't open file " << filename;
        exit(EXIT_FAILURE);
    }

}

std::string Board::toString() const
{
    std::string result = "";
    for (int i = 0; i < DIMENSION; i++) {
        // Print horizontal line
        if (i % 3 == 0) {
            for (int j = 0; j < 25; j++) {
                result += "-";
            }
            result += "\n";
        }

        // Print line of numbers
        for (int j = 0; j < DIMENSION; j++) {
            if (j % 3 == 0) // with vertical line
                result += "| ";
            int index = i * DIMENSION + j;
            if (_numbers[index] == NO_NUMBER) {
                result += " ";
            }
            else {
                result += '0' + _numbers[index];
            }
            result +=  " ";
        }
        result += "|\n";
    }

    // Print one last horizontal line
    for (int j = 0; j < 25; j++) {
        result += "-";
    }
    result += "\n";

    return result;
}

Board::Board(const Board & b)
{
    _numbers = new int[NB_CELLS];
    for (int i = 0; i < NB_CELLS; i++) {
        _numbers[i] = b._numbers[i];
    }
}

Board& Board::operator=(const Board b)
{
    _numbers = b._numbers;
    return *this;
}

void Board::applyMove(int index, int number)
{
    _numbers[index] = number;
}

void Board::undoMove(int index)
{
    _numbers[index] = NO_NUMBER;
}

int Board::getFirstEmptyCell() const
{
    for (int i = 0; i < NB_CELLS; i++) {
        if (_numbers[i] == NO_NUMBER)
            return i;
    }
    return -1;
}

void Board::getCandidates(int index, int *candidates, int &nbCandidates) const
{
    bool isCandidate[DIMENSION+1]; // we ignore the [0] cell, numbers are from 1 to 9
    for (int i = 1; i <= DIMENSION; i++)
        isCandidate[i] = true;

    // Line
    int firstOfLine = index - (index % DIMENSION);
    for (int i = firstOfLine; i < firstOfLine + DIMENSION; i++) {
        int number = _numbers[i];
        if (number != NO_NUMBER)
            isCandidate[number] = false;
    }

    // Column
    int firstOfCol = index % 9;
    for (int i = firstOfCol; i < NB_CELLS; i += DIMENSION) {
        int number = _numbers[i];
        if (number != NO_NUMBER)
            isCandidate[number] = false;
    }

    // Zone
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

    nbCandidates = 0;
    for (int i = 1; i <= DIMENSION; i++) {
        if (isCandidate[i]) {
            candidates[nbCandidates] = i;
            nbCandidates++;
        }
    }
}

// inline
// int Board::indexFromCoord(int x, int y)
// {
// return x * DIMENSION + y;
// }

// inline
// void Board::coordFromIndex(int index, int &x, int &y)
// {
// x = index / DIMENSION;
// y = index % DIMENSION;
// }