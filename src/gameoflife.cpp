#include "gameoflife.h"

#include <cassert>
#include <cstdlib>
#include <ostream>
#include <random>

// public:

GameOfLife::GameOfLife(const SizeType width, const SizeType height)
:_width{width},
_height{height},
_cellData{std::vector<uint8_t>(getNumberOfCells(), 0)}
{}

GameOfLife::SizeType GameOfLife::getWidth() const
{
    return _width;
}

GameOfLife::SizeType GameOfLife::getHeight() const
{
    return _height;
}

GameOfLife::SizeType GameOfLife::getNumberOfCells() const
{
    // total number of cells in the grid
    return getWidth()*getHeight();
}

bool GameOfLife::isCellAlive(const SizeType x, const SizeType y) const
{
    // only take the dead/alive status contained in the position stateBit
    return getCellData(x, y) & (1 << stateBit);
}

void GameOfLife::toggleCellState(const SizeType x, const SizeType y)
{
    toggleCellStatusWithoutUpdate(x, y);
    updateNeighbours(x, y);
}

void GameOfLife::applyRandomState()
{
    static const time_t seed = time(NULL); // generate static seed
    static std::default_random_engine generator(seed);
    static std::uniform_real_distribution<float> distribution(0.0f,1.0f); // uniform distribution for shape and cell state generation

    reset(); // kill all cells

    for (SizeType i = 0; i < getHeight(); ++i)
    {
        for (SizeType j = 0; j < getWidth(); ++j)
        {
            const float randomNumber = distribution(generator);
            if (randomNumber < 0.5) // resurrect cells with probability 50%
                toggleCellState(i, j);
        }
    }

    return;
}

void GameOfLife::reset()
{
    // kill all cells
    for (SizeType i = 0; i < getHeight(); ++i)
    {
        for (SizeType j = 0; j < getWidth(); ++j)
        {
            accessCellData(i, j) = 0x00;
        }
    }

    return;
}

void GameOfLife::nextGeneration()
{
    // reserve some space
    std::vector<SizeType> coordinatesToToggle;
    coordinatesToToggle.reserve(getNumberOfCells()/2);

    // save the coordinates, which are going to be toggled
    // this is necessary, as toggling the cell state automatically changes the number of neighbours.
    // so for a right development of the next generation, the current state mustn't be changed
    // until all cells which are going to be toggled are known
    for (SizeType i = 0; i < getHeight(); ++i)
    {
        for (SizeType j = 0; j < getWidth(); ++j)
        {
            if (isCellAlive(i, j))
            {
                // cells to be killed
                if (getNumberOfNeighbours(i, j) != 2 && getNumberOfNeighbours(i,j) != 3)
                {
                    coordinatesToToggle.push_back(i);
                    coordinatesToToggle.push_back(j);
                }
            }
            else
            {
                // cells to be resurrected
                if(getNumberOfNeighbours(i, j) == 3)
                {
                    coordinatesToToggle.push_back(i);
                    coordinatesToToggle.push_back(j);
                }
            }
        }
    }

    // now, toggle these cells
    for (SizeType i = 0; i < static_cast<SizeType>(coordinatesToToggle.size()); i += 2)
    {
        toggleCellState(coordinatesToToggle[i], coordinatesToToggle[i+1] );
    }

    return;
}

void GameOfLife::print(std::ostream &outputStream) const
{
    for (SizeType i = 0; i < getHeight(); ++i)
    {
        for (SizeType j = 0; j < getWidth(); ++j)
            outputStream << isCellAlive(i, j) << " ";
        outputStream << std::endl;
    }
    return;
}

void GameOfLife::printNeighbours(std::ostream &outputStream) const
{
    for (SizeType i = 0; i < getHeight(); ++i)
    {
        for (SizeType j = 0; j < getWidth(); ++j)
            outputStream << getNumberOfNeighbours(i, j) << " ";
        outputStream << std::endl;
    }
    return;
}

// private:

uint8_t GameOfLife::getCellData(const SizeType x, const SizeType y) const
{
    return _cellData[x + y * _width];
}

uint8_t& GameOfLife::accessCellData(const SizeType x, const SizeType y)
{
    return _cellData[x + y * _width];
}

int GameOfLife::getNumberOfNeighbours(const SizeType x, const SizeType y) const
{
    // since the stateBit-th bit is used for the state, we have to shift to the right accordingly
    return getCellData(x, y) >> (stateBit + 1);
}

void GameOfLife::setNumberOfNeighbours(const SizeType x, const SizeType y, const int number)
{
    assert(0 <= number && number <= 8 && "ERROR: Tried to set invalid number of neighbours!");
    // clear number of neighbours
    accessCellData(x, y) &= (1 << stateBit);
    // set number of neighbours
    accessCellData(x, y) |= (number << (stateBit + 1));
    return;
}

void GameOfLife::addToNumberOfNeighbours(const SizeType x, const SizeType y, const int number)
{
    // for each cell, the number of neighbours can only change by +-1 in each step
    assert((number == -1 || number == 1) && "ERROR: Invalid number!");

    // when toggling cells on the boundary of the game board, non-existing neighbours outside the boundary could be
    // toggled. To stop this, only toggle cells which exist.
    if (0 <= x && x < getHeight() && 0 <= y && y < getWidth())
    {
        int newNumber = getNumberOfNeighbours(x, y) + number;
        setNumberOfNeighbours(x, y, newNumber);
    }
    return;
}

void GameOfLife::updateNeighbours(const SizeType x, const SizeType y)
{
    int number;
    if (isCellAlive(x, y))
        number = 1; // if new cell is alive, all neighbour cells now have a new neighbour
    else
        number = -1; // else, they have lost one neighbour

    // add number to each of the neighbour cells
    for (int i_offset = -1; i_offset <= 1; ++i_offset)
        for (int j_offset = -1; j_offset <= 1; ++j_offset)
            if (i_offset != 0 || j_offset != 0) // but do not add it for the cell itself
                addToNumberOfNeighbours(x + i_offset, y + j_offset, number);

    return;
}

void GameOfLife::toggleCellStatusWithoutUpdate(const SizeType x, const SizeType y)
{
    accessCellData(x, y) ^= (1 << stateBit);
}

uint8_t GameOfLife::stateBit = 0; // rightmost bit defines the position for dead/alive state
