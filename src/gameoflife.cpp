/*
 * GameOfLife.cpp
 *
 *  Created on: Oct 18, 2020
 *      Author: tristan
 */

#include "gameoflife.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

// public:

GameOfLife::GameOfLife(const SizeType width, const SizeType height)
: _width(width), _height(height)
{
	_cellData = std::vector<uint8_t>(getNumberOfCells());
}

GameOfLife::~GameOfLife()
{
	// TODO Auto-generated destructor stub
}

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
	return getWidth()*getHeight();
}

bool GameOfLife::isCellAlive(const SizeType i, const SizeType j) const
{
	return getCellData(i, j) & statusBit;
}

void GameOfLife::toggleCellState(const SizeType i, const SizeType j)
{
	toggleCellStatusWithoutUpdate(i, j);
	updateNeighbours(i, j);
}

void GameOfLife::applyRandomState()
{
	reset();

	for (SizeType i = 0; i < getHeight(); ++i)
		for (SizeType j = 0; j < getWidth(); ++j)
		{
			const double randomNumber = rand()/static_cast<double>(RAND_MAX);
			if (randomNumber < 0.5)
				toggleCellState(i, j);
		}

	return;
}

void GameOfLife::print() const
{
	for (SizeType i = 0; i < getHeight(); ++i)
	{
		for (SizeType j = 0; j < getWidth(); ++j)
			std::cout << isCellAlive(i, j) << " ";
		std::cout << std::endl;
	}
	return;
}

void GameOfLife::printNeighbours() const
{
	for (SizeType i = 0; i < getHeight(); ++i)
	{
		for (SizeType j = 0; j < getWidth(); ++j)
			std::cout << getNumberOfNeighbours(i, j) << " ";
		std::cout << std::endl;
	}
	return;
}

void GameOfLife::reset()
{
	for (SizeType i = 0; i < getHeight(); ++i)
		for (SizeType j = 0; j < getWidth(); ++j)
			accessCellData(i, j) = 0x00;
	return;
}

void GameOfLife::nextGeneration()
{
	std::vector<SizeType> coordinatesToToggle;
	coordinatesToToggle.reserve(getNumberOfCells()/2);

	for (SizeType i = 0; i < getHeight(); ++i)
		for (SizeType j = 0; j < getWidth(); ++j)
			if (isCellAlive(i, j))
			{
				// kill cells
				if (getNumberOfNeighbours(i, j) != 2 && getNumberOfNeighbours(i,j) != 3)
				{
					coordinatesToToggle.push_back(i);
					coordinatesToToggle.push_back(j);
				}
			}
			else
			{
				// resurrect cells
				if(getNumberOfNeighbours(i, j) == 3)
				{
					coordinatesToToggle.push_back(i);
					coordinatesToToggle.push_back(j);
				}
			}

	for (SizeType i = 0; i < static_cast<SizeType>(coordinatesToToggle.size()); i += 2)
	{
		toggleCellState(coordinatesToToggle[i], coordinatesToToggle[i+1] );
	}

	return;
}

// private:

uint8_t GameOfLife::getCellData(const SizeType i, const SizeType j) const
{
	return _cellData[i + j*_width];
}

uint8_t& GameOfLife::accessCellData(const SizeType i, const SizeType j)
{
	return _cellData[i + j*_width];
}

int GameOfLife::getNumberOfNeighbours(const SizeType i, const SizeType j) const
{
	return getCellData(i, j) >> statusBit;
}

void GameOfLife::setNumberOfNeighbours(const SizeType i, const SizeType j, const int number)
{
	assert(0 <= number && number <= 8 && "ERROR: Tried to set invalid number of neighbours!");
	// clear number of neighbours
	accessCellData(i, j) &= statusBit;
	// set number of neighbours
	accessCellData(i, j) |= (number << statusBit);
	return;
}

void GameOfLife::addToNumberOfNeighbours(const SizeType i, const SizeType j, const int number)
{
	assert((number == -1 || number == 1) && "ERROR: Invalid number!");
	if (0 <= i && i < getHeight() && 0 <= j && j < getWidth())
	{
		int newNumber = getNumberOfNeighbours(i, j) + number;
		setNumberOfNeighbours(i, j, newNumber);
	}
	return;
}

void GameOfLife::updateNeighbours(const SizeType i, const SizeType j)
{
	int number = 0;
	if (isCellAlive(i, j))
		number = 1;
	else
		number = -1;

	for (int i_offset = -1; i_offset <= 1; ++i_offset)
		for (int j_offset = -1; j_offset <= 1; ++j_offset)
			if (i_offset != 0 || j_offset != 0)
				addToNumberOfNeighbours(i + i_offset, j + j_offset, number);

	return;
}

void GameOfLife::toggleCellStatusWithoutUpdate(const SizeType i, const SizeType j)
{
	accessCellData(i, j) ^= statusBit;
}

uint8_t GameOfLife::statusBit = 0x01;
