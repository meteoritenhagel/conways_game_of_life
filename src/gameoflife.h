#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <cstdint>
#include <ostream>
#include <vector>

class GameOfLife {
public:
    using SizeType = int;

    /*
     * Constructor.
     * Initializes game board with the correct dimensions.
     *
     * @param[in] width game board width
     * @param[in] height game board height
     */
    GameOfLife(const SizeType width, const SizeType height);
    ~GameOfLife() = default;

    /*
     * Returns game board width.
     * @return width
     */
    SizeType getWidth() const;

    /*
     * Returns game board height.
     * @return height
     */
    SizeType getHeight() const;

    /*
     * Returns total number of cells.
     * @return total number of cells
     */
    SizeType getNumberOfCells() const;

    /*
     * Returns number of neighbours of cell with coordinates (x,y).
     *
     * @param[in] x x-coordinate
     * @param[in] y y-coordinate
     * @return number of neighbours
     */
    int getNumberOfNeighbours(const SizeType x, const SizeType y) const;

    /*
     * Returns whether the cell with coordinates (x,y) is alive.
     *
     * @param[in] x x-coordinate
     * @param[in] y y-coordinate
     * @return true if cell is alive
     */
    bool isCellAlive(const SizeType x, const SizeType y) const;

    /*
     * Toggle state of the cell with coordinates (x,y).
     * I.e. alive cells become dead and vice versa.
     *
     * @param[in] x x-coordinate
     * @param[in] y y-coordinate
     */
    void toggleCellState(const SizeType x, const SizeType y);

    /*
     * Resets the board to a uniformly distributed grid of alive and dead cells.
     */
    void applyRandomState();

    /*
     * Resets the board such that all cells are dead.
     */
    void reset();

    /*
     * Advances the game to the next generation
     */
    void nextGeneration();

    /*
     * Prints the cell states as a grid into an output stream.
     * @param[in] outputStream output stream
     */
    void print(std::ostream &outputStream) const;

    /*
     * Prints the cell neighbours of each cell as a grid into an output stream.
     * @param[in] outputStream output stream
     */
    void printNeighbours(std::ostream &outputStream) const;

private:
    /*
     * Returns the cell data of the cell with the coordinates (x,y).
     *
     * @param[in] x x-coordinate
     * @param[in] y y-coordinate
     * @return cell data
     */
    uint8_t getCellData(const SizeType x, const SizeType y) const;

    /*
     * Directly accesses the cell data of the cell with the coordinates (x,y).
     * Attention: Modifying the returned reference also modifies the grid's cell data!
     *
     * @param[in] x x-coordinate
     * @param[in] y y-coordinate
     * @return reference to cell data
     */
    uint8_t& accessCellData(const SizeType x, const SizeType y);

    /*
     * Set the number of neighbours of the cell with the coordinates (x,y).
     * Also checks if the desired number is valid, i.e. 1 <= number <= 8.
     *
     * @param[in] x x-coordinate
     * @param[in] y y-coordinate
     * @param[in] number
     */
    void setNumberOfNeighbours(const SizeType x, const SizeType y, const int number);

    /*
     * Adds the given number to the current number of neighbours of the cell with the coordinates (x,y).
     * This method is invoked on all of a cell's neighbours when toggling it.
     * If a cell on the boundary is toggled, non-existent neighbours outside the game board could be toggled.
     * In such a case, this method has no effect.
     *
     * @param[in] x x-coordinate
     * @param[in] y y-coordinate
     * @param[in] number
     */
    void addToNumberOfNeighbours(const SizeType x, const SizeType y, const int number);

    /*
     * Updates the number of neighbours of the cell with the coordinates (x,y).
     * After toggling a cell, this function is used to update the number of neighbours to the right value.
     *
     * @param[in] x x-coordinate
     * @param[in] y y-coordinate
     */
    void updateNeighbours(const SizeType x, const SizeType y);

    /*
     * Toggles the cell with the coordinates (x,y) without updating the number of neighbours.
     * After using that, calling updateNeighbours is highly recommended!
     *
     * @param[in] x x-coordinate
     * @param[in] y y-coordinate
     */
    void toggleCellStatusWithoutUpdate(const SizeType x, const SizeType y);

private:
    static uint8_t stateBit; ///< defines the bit in each uint8_t cell data used for storing the alive/dead state

    SizeType _width; ///< width of game board
    SizeType _height; ///< height of game board
    std::vector<uint8_t> _cellData; ///< array of cell data, storing number of neighbours and the state for all cells
};

#endif /* GAMEOFLIFE_H_ */
