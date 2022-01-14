#ifndef CELL_H
#define CELL_H

/*!
 * \brief The Cell struct is the structure object for all the cells in the Sudoku.
 */

struct Cell
{
    /*!
     * \brief The default and parameterized constrcutor.
     * \param y is the row coordinate
     * \param x is the column coordinate
     * \param num is the number the cell holds (can be between 0-9)
     * \param assigned is true if the cell has been assigned a number between 1-9. Set to false if it has been assigned number 0.
     */
    Cell(int y = 0, int x = 0, int num = 0, bool assigned = false) : y(y), x(x), num(num), assigned(assigned) {}
    int y;
    int x;
    int num;
    bool assigned;
};

#endif // CELL_H
