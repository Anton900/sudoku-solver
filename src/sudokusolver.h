#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <algorithm>
#include <vector>
#include "cell.h"

/*!
 * \brief The SudokuSolver is the class to solve Sudoku puzzles.
 */

class SudokuSolver
{
public:
    SudokuSolver(std::vector<std::vector<int>> grid);
    /*!
     * \brief Parametrized constructor.
     * \param grid The 2d vector<vector<cell>> container that contains the puzzle to solve.
     */
    SudokuSolver(std::vector<std::vector<Cell>> grid);
    ~SudokuSolver(){}

    /*!
     * \brief The recursive backtrack method used to solve the puzzle.
     *
     * The method will first check if alls cells solved. If not, search for the first unassigned cell and check possible values for it.
     * If possible value are found, set it to that value and search for next unassigned cell.
     * If no possible values are found then return false and set value to 0 on previous cell and search for new possible value on this cell.
     * Continue until all unassigned cells are searched.
     *
     * \return true if the puzzle was solved
     */
    bool backTrackSolve();
    /*!
     * \brief Searches rows, columns and minigrids if the number exists
     * \param numToFind is the number to find
     * \param rowNum is the row to search
     * \param colNum is the column to search
     * \return
     */
    bool searchAll(int numToFind, int rowNum, int colNum);
    /*!
     * \brief Searches row for the number to find
     * \param numToFind is the number to find
     * \param rowNum is the row to search
     * \return
     */
    bool searchRow(int numToFind, int rowNum);
    /*!
     * \brief Searches column for the number to find
     * \param numToFind is the number to find
     * \param colNum is the column to search
     * \return
     */
    bool searchCol(int numToFind, int colNum);
    /*!
     * \brief Searches minigrid for the number to find
     * \param numToFind is the number to find
     * \param rowNum is the row to search
     * \param colNum is the column to search
     * \return
     */
    bool searchMiniGrid(int numToFind, int rowNum, int colNum);
    /*!
     * \brief If cell
     * \param rowNum
     * \param colNum
     * \return
     */
    bool isUnsolvedCell(int rowNum, int colNum);
    /*!
     * \brief Searches through the grid container for a unassigned cell
     * \return true if no matching cells could be found
     */
    bool allCellsSolved();
    /*!
     * \brief Method for calling the solution grid
     * \return the solutiongrid
     */
    std::vector<std::vector<Cell>> getSolution();

    /*!
     * \brief Search through the grid for cell that is unassigned
     * \return the first cell that is unassigned
     */
    Cell& findUnassignedCell();

private:
    std::vector<std::vector<Cell>> solutionGrid;

};

#endif
