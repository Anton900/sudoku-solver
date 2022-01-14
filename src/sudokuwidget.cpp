#include "sudokuwidget.h"


SudokuWidget::SudokuWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout();
    sudokuGrid = new QGridLayout();
    QValidator *validator = new QIntValidator(1, 9, this);
    for(int row = 0; row < 9; row++)
    {
        displayGrid.append(QVector<QLineEdit*>());
        for(int col = 0; col < 9; col++)
        {
            QLineEdit *cell = new QLineEdit();
            cell->setFixedSize(35, 35);
            cell->setAlignment(Qt::AlignCenter);
            cell->setValidator(validator);
            if ((row == 2 || row == 5) && (col == 2 || col == 5))
            {
                cell->setStyleSheet("margin-right: 15px; margin-bottom: 15px");
                cell->setFixedSize(50, 50);
            }
            else if (row == 2 || row == 5)
            {
                cell->setStyleSheet("margin-bottom: 15px");
                cell->setFixedHeight(50);
            }
            else if (col == 2 || col == 5)
            {
                cell->setStyleSheet("margin-right: 15px");
                cell->setFixedWidth(50);
            }
            sudokuGrid->addWidget(cell, row, col);
            displayGrid[row].append(cell);

        }
    }

    buttons = new QHBoxLayout();
    QPushButton *solve = new QPushButton("Solve");
    QPushButton *reset = new QPushButton("Reset");
    QPushButton *clear = new QPushButton("Clear");

    connect(solve, SIGNAL(clicked()), this, SLOT(solve()));
    connect(reset, SIGNAL(clicked()), this, SLOT(reset()));
    connect(clear, SIGNAL(clicked()), this, SLOT(clear()));

    buttons->addWidget(solve);
    buttons->addWidget(reset);
    buttons->addWidget(clear);

    //fileLabel = new QLabel("med puzzle 123");

    //layout ->addWidget(fileLabel, 0, 0);
    layout->addLayout(sudokuGrid, 1, 0);
    layout->addLayout(buttons, 2, 0);

    this->setLayout(layout);

}

void SudokuWidget::updateDisplayGrid(std::vector<std::vector<Cell>> updateCells)
{
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            if(updateCells[row][col].num != 0)
            {
                int value = updateCells[row][col].num;
                displayGrid[row][col]->setText(QString::number(value));
                displayGrid[row][col]->setReadOnly(true);
            }
        }
    }
}

void SudokuWidget::solve()
{
    if(grid.empty())
    {
        QMessageBox messageBox;
        messageBox.setWindowTitle(tr("Information"));
        messageBox.setText(tr("You need to open a Sudoku file to solve."));
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.setDefaultButton(QMessageBox::Ok);
        if (messageBox.exec() == QMessageBox::Ok)
            return;
    }

    SudokuSolver solver(grid);
    updateDisplayGrid(solver.getSolution());
}

void SudokuWidget::reset()
{
    if(grid.empty())
    {
        return;
    }
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            if(grid[row][col].num == 0)
            {
                displayGrid[row][col]->setText("");
                displayGrid[row][col]->setReadOnly(false);
            }
        }
    }
}

void SudokuWidget::clear()
{
    QMessageBox messageBox;
    messageBox.setWindowTitle(tr("Confirmation"));
    messageBox.setText(tr("Do you really want to clear?"));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);
    if (messageBox.exec() == QMessageBox::Yes)
    {
        grid.clear();
        clearGrid();
    }
}

std::vector<std::vector<Cell>> SudokuWidget::getGrid()
{
    return grid;
}

void SudokuWidget::setGrid(std::vector<std::vector<Cell>> vec)
{
    grid.resize(9);
    for (int i = 0; i < 9; i++)
        grid[i].resize(9);
    std::copy(vec.begin(), vec.end(), grid.begin());
}

void SudokuWidget::clearGrid()
{
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
                displayGrid[row][col]->setText("");
                displayGrid[row][col]->setReadOnly(false);
        }
    }
}

QVector<QVector<QLineEdit*>> SudokuWidget::getCurrentDisplayGrid()
{
    return displayGrid;
}
