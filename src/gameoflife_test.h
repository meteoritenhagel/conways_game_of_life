#ifndef GAMEOFLIFE_TEST_H_
#define GAMEOFLIFE_TEST_H_

#include <map>
#include <string>

class GameOfLife_Test {
public:
	GameOfLife_Test() = default;
	virtual ~GameOfLife_Test() = default;

	void testAll();

	void testTogglingCellStatus();
	void testNeighbourUpdateWhenAddingCell();
	void testNeighbourUpdateWhenRemovingCell();
	void testNeighbourUpdateWhenAddingAndRemovingCell();
	void testComplexGridNeighbours();

private:
	static std::map<bool, std::string> testPassedMessage;
};

#endif /* GAMEOFLIFE_TEST_H_ */
