#include "sudokusolver.h"
#include <iostream>

SudokuSolver::SudokuSolver(std::vector<std::vector<int>> grid)
{
    solutionGrid.resize(9);
    for (int i = 0; i < 9; i++)
        solutionGrid[i].resize(9);
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            this->solutionGrid[row][col].num = grid[row][col];
            this->solutionGrid[row][col].y = row;
            this->solutionGrid[row][col].x = col;
            if(grid[row][col])
                this->solutionGrid[row][col].assigned = true;
            else
                this->solutionGrid[row][col].assigned = false;
        }
    }
    backTrackSolve();
}

SudokuSolver::SudokuSolver(std::vector<std::vector<Cell>> grid)
{
    solutionGrid.resize(9);
    for (int i = 0; i < 9; i++)
        solutionGrid[i].resize(9);
    std::copy(grid.begin(), grid.end(), solutionGrid.begin());
    backTrackSolve();
}


bool SudokuSolver::backTrackSolve()
{

    if (allCellsSolved())
        return true;
    Cell currentCell = findUnassignedCell();
    int rowNum = currentCell.y;
    int colNum = currentCell.x;
    for (int numToFind = currentCell.num + 1; numToFind < 10; numToFind++)
    {
        if (searchAll(numToFind, rowNum, colNum))
        {
            //std::cout << "(" << rowNum << ", " << colNum << "): " << numToFind << "\n";
            solutionGrid[rowNum][colNum].num = numToFind;
            solutionGrid[rowNum][colNum].assigned = true;
            if (backTrackSolve())
                return true;
            else
            {
                solutionGrid[rowNum][colNum].num = 0;
                solutionGrid[rowNum][colNum].assigned = false;
            }
        }
        if (numToFind == 9)
        {
            return false;
        }
    }
    return false;
}

bool SudokuSolver::allCellsSolved()
{

    /*
    auto it = std::find_if(solutionGrid.begin(), solutionGrid.end(), SearchCellUnassigned());

    return true;*/

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (solutionGrid[i][j].assigned == false)
                return false;
        }
    }
    return true;
}

bool SudokuSolver::isUnsolvedCell(int rowNum, int colNum)
{
    if (solutionGrid[rowNum][colNum].num == 0 && solutionGrid[rowNum][colNum].assigned == false)
        return true;
    return false;
}

bool SudokuSolver::searchAll(int numToFind, int rowNum, int colNum)
{
    if (!searchRow(numToFind, rowNum) && !searchCol(numToFind, colNum) && !searchMiniGrid(numToFind, rowNum, colNum))
        return true;
    return false;
}

bool SudokuSolver::searchRow(int numToFind, int rowNum)
{
    std::vector<Cell> row = solutionGrid[rowNum];
    auto it = std::find_if(row.begin(), row.end(), [&](const Cell& cell)
        { return cell.num == numToFind; });
    if (it != row.end())
        return true;
    return false;
}

bool SudokuSolver::searchCol(int numToFind, int colNum)
{
    auto itCol = std::find_if(solutionGrid.begin(), solutionGrid.end(), [&](std::vector<Cell> e)
        { return numToFind == e[colNum].num; });
    if (itCol != solutionGrid.end())
    {
        return true;
    }
    return false;
}
bool SudokuSolver::searchMiniGrid(int numToFind, int rowNum, int colNum)
{
    int boxRow = rowNum - rowNum % 3;
    int boxCol = colNum - colNum % 3;
    for (int i = boxRow; i < boxRow + 3; i++)
    {
        for (int j = boxCol; j < boxCol + 3; j++)
        {
            if (numToFind == solutionGrid[i][j].num)
            {
                return true;
            }
        }
    }
    return false;
}

Cell& SudokuSolver::findUnassignedCell()
{
    Cell cell(0, 0, 0, true);

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(solutionGrid[i][j].assigned == false)
                return solutionGrid[i][j];
        }
    }

    return cell;
}

std::vector<std::vector<Cell>> SudokuSolver::getSolution()
{
    return solutionGrid;
}
