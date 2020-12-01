/*
 * gameoflife_test.cpp
 *
 *  Created on: Oct 19, 2020
 *      Author: tristan
 */

#include "gameoflife_test.h"

#include "gameoflife.h"

#include <iostream>

void GameOfLife_Test::testAll()
{
	testTogglingCellStatus();
	testNeighbourUpdateWhenAddingCell();
	testNeighbourUpdateWhenAddingAndRemovingCell();
	testComplexGridNeighbours();
}

void GameOfLife_Test::testTogglingCellStatus()
{
	bool testPassed = true;

	GameOfLife game(5, 5);

	const GameOfLife::SizeType i_toggle = 2;
	const GameOfLife::SizeType j_toggle = 3;

	game.toggleCellState(i_toggle, j_toggle);

	for (GameOfLife::SizeType i = 0; i < game.getHeight(); ++i)
		for (GameOfLife::SizeType j = 0; j < game.getWidth(); ++j)
		{
			if (i == i_toggle && j == j_toggle)
				testPassed = testPassed && game.isCellAlive(i, j);
			else
				testPassed = testPassed && !(game.isCellAlive(i, j));
		}

	std::cout << "testTogglingCellStatus: " << testPassedMessage[testPassed] << std::endl;
	return;
}

void GameOfLife_Test::testNeighbourUpdateWhenAddingCell()
{
	bool testPassed = true;
	const int size = 5;

	GameOfLife game(size, size);

	game.toggleCellState(2, 3);
	game.toggleCellState(1, 1);

	const int correctNeighbours[size][size] = {1, 1, 1, 0, 0,
											   1, 0, 2, 1, 1,
											   1, 1, 2, 0, 1,
											   0, 0, 1, 1, 1,
											   0, 0, 0, 0, 0};

	for (GameOfLife::SizeType i = 0; i < game.getHeight(); ++i)
		for (GameOfLife::SizeType j = 0; j < game.getWidth(); ++j)
			testPassed = testPassed && (game.getNumberOfNeighbours(i, j) == correctNeighbours[i][j]);

	std::cout << "testNeighbourUpdateWhenAddingCell: " << testPassedMessage[testPassed] << std::endl;
	return;
}

void GameOfLife_Test::testNeighbourUpdateWhenAddingAndRemovingCell()
{
	bool testPassed = true;
	const int size = 5;

	GameOfLife game(size, size);

	game.toggleCellState(2, 3);
	game.toggleCellState(1, 1);
	game.toggleCellState(2, 3);

	const int correctNeighbours[size][size] = {
			1, 1, 1, 0, 0,
			1, 0, 1, 0, 0,
			1, 1, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0
	};

	for (GameOfLife::SizeType i = 0; i < game.getHeight(); ++i)
		for (GameOfLife::SizeType j = 0; j < game.getWidth(); ++j)
			testPassed = testPassed && (game.getNumberOfNeighbours(i, j) == correctNeighbours[i][j]);

	std::cout << "testNeighbourUpdateWhenAddingAndRemovingCell: " << testPassedMessage[testPassed] << std::endl;
	return;
}

void GameOfLife_Test::testComplexGridNeighbours()
{
	bool testPassed = true;
	const int size = 5;

	GameOfLife game(size, size);

	game.toggleCellState(0, 1);
	game.toggleCellState(1, 0);
	game.toggleCellState(1, 1);
	game.toggleCellState(1, 3);
	game.toggleCellState(2, 0);
	game.toggleCellState(2, 2);
	game.toggleCellState(3, 3);
	game.toggleCellState(4, 0);
	game.toggleCellState(4, 1);
	game.toggleCellState(4, 2);
	game.toggleCellState(4, 4);

	const int correctNeighbours[size][size] = {
			3, 2, 3, 1, 1,
			3, 4, 4, 1, 1,
			2, 4, 3, 3, 2,
			3, 5, 4, 3, 2,
			1, 2, 2, 3, 1
	};

	for (GameOfLife::SizeType i = 0; i < game.getHeight(); ++i)
		for (GameOfLife::SizeType j = 0; j < game.getWidth(); ++j)
			testPassed = testPassed && (game.getNumberOfNeighbours(i, j) == correctNeighbours[i][j]);

	std::cout << "testComplexGridNeighbours: " << testPassedMessage[testPassed] << std::endl;
	return;
}

std::map<bool, std::string> GameOfLife_Test::testPassedMessage = {
		{true,  "passed"},
		{false, "FAILED"}
};
