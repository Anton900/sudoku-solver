#ifndef SUDOKUWIDGET_H
#define SUDOKUWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QValidator>
#include <QVector>
#include <QList>
#include <vector>
#include <QLabel>
#include "sudokusolver.h"

/*!
 * \brief The SudokuWidget class is the class responsible for the Sudoku components on the GUI: the grid and buttons.
 */

class SudokuWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief CTOR for SudokuWidget
     * \param parent paramter for the baseclass QWidget, set to nullptr if no arguments given
     */
    SudokuWidget(QWidget *parent = nullptr);

    /*!
     * \brief Update the displayed grid from the 2d vector grid
     * \param The 2d cell vector that will updated from
     */
    void updateDisplayGrid(std::vector<std::vector<Cell>> updateCells);

    /*!
     * \brief Getter for the 2d cell vector
     * \return The 2d cell vector will be returned
     */
    std::vector<std::vector<Cell>> getGrid();
    /*!
     * \brief Setter for the 2d cell vector
     * \param vec is the vec to be set to
     */
    void setGrid(std::vector<std::vector<Cell>> vec);

    /*!
     * \brief Getter for the display grid
     * \return The 2d display grid
     */
    QVector<QVector<QLineEdit*>> getCurrentDisplayGrid();

    void clearGrid();

private slots:
    /*!
     * \brief If no grid is opened, display QMessageBox.
     * Otherwise use SudokuSolver class to solve the puzzle grid
     */
    void solve();
    /*!
     * \brief If puzzle grid is solved, then change display grid to unsolved again
     */
    void reset();
    /*!
     * \brief Clear both grids to empty
     */
    void clear();

private:
    QMenu *fileMenu;
    QGridLayout *layout;
    QGridLayout *sudokuGrid;
    QHBoxLayout *buttons;
    QVector<QVector<QLineEdit*>> displayGrid;
    std::vector<std::vector<Cell>> grid;

};

#endif // SUDOKUWIDGET_H
