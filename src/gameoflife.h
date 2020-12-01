/*
 * GameOfLife.h
 *
 *  Created on: Oct 18, 2020
 *      Author: tristan
 */

#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <cstdint>
#include <vector>

class GameOfLife {
public:
	using SizeType = int;

	GameOfLife(const SizeType width, const SizeType height);
	virtual ~GameOfLife();

	SizeType getWidth() const;
	SizeType getHeight() const;
	SizeType getNumberOfCells() const;

	int getNumberOfNeighbours(const SizeType i, const SizeType j) const;

	bool isCellAlive(const SizeType i, const SizeType j) const;
	void toggleCellState(const SizeType i, const SizeType j);

	void applyRandomState();

	void print() const;
	void printNeighbours() const;

	void reset();

	void nextGeneration();

private:
	static uint8_t statusBit;

	SizeType _width;
	SizeType _height;
	std::vector<uint8_t> _cellData;

	uint8_t getCellData(const SizeType i, const SizeType j) const;
	uint8_t& accessCellData(const SizeType i, const SizeType j);

	void setNumberOfNeighbours(const SizeType i, const SizeType j, const int number);
	void addToNumberOfNeighbours(const SizeType i, const SizeType j, const int number);
	void updateNeighbours(const SizeType i, const SizeType j);
	void toggleCellStatusWithoutUpdate(const SizeType i, const SizeType j);
};

#endif /* GAMEOFLIFE_H_ */
