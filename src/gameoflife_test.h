#ifndef GAMEOFLIFE_TEST_H_
#define GAMEOFLIFE_TEST_H_

#include <map>
#include <string>

/*
 * This class is used for checking the correctness of the implementation of Conway's Game of Life in
 * class GameOfLife
 */
class GameOfLife_Test {
public:
    /*
     * Constructor.
     */
    GameOfLife_Test() = default;

    /*
     * Destructor.
     */
    ~GameOfLife_Test() = default;

    /*
     * Invokes all tests below.
     * Important: When adding a new test to this class, also include it here!
     */
    void testAll();

    /*
     * Test if toggling a cell state works correctly.
     */
    void testTogglingCellState();

    /*
     * Test if neighbours are calculated correctly when adding cells.
     */
    void testNeighbourUpdateWhenAddingCell();

    /*
     * Test if neighbours are calculated correctly when adding and then removing a cell.
     */
    void testNeighbourUpdateWhenAddingAndRemovingCell();

    /*
     * Test if neighbours are calculated correctly for a more complex grid.
     */
    void testComplexGridNeighbours();

private:
    static std::map<bool, std::string> testPassedMessage; ///< Message to display in dependence of a boolean
};

#endif /* GAMEOFLIFE_TEST_H_ */
