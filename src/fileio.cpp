#include "fileio.h"
#include <iostream>

bool FileIO::openFile()
{
    if(path.isEmpty() || !validSudokuFile())
        return false;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly))
        return false;

    return true;
}

vector<vector<Cell>> FileIO::read()
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {

    }
    QTextStream stream(&file);
    grid.resize(9);
    for (int i = 0; i < 9; i++)
        grid[i].resize(9);
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {

            int value;
            stream >> value;

            grid[row][col].num = value;
            grid[row][col].y = row;
            grid[row][col].x = col;
            if(value)
                grid[row][col].assigned = true;
            else
                grid[row][col].assigned = false;
        }
    }
    file.close();

    return grid;
}

void FileIO::write(QVector<QVector<QLineEdit*>> puzzleGrid)
{
    if (path != "")
    {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        }
        else
        {
            QTextStream stream(&file);
            for(int row = 0; row < 9; row++)
            {
                for(int col = 0; col < 9; col++)
                {
                    if(puzzleGrid[row][col]->text() == "")
                        stream << 0;
                    else
                        stream << puzzleGrid[row][col]->text();
                    if(col != 8)
                        stream << " ";
                    else
                        stream << "\n";
                }
            }
            file.close();
        }
    }

}

void FileIO::setPath(QString path)
{
    this->path = path;
}

bool FileIO::validSudokuFile()
{
    std::string pathStr = path.toStdString();
    std::ifstream input(pathStr, std::fstream::in);
    if(input.fail()){
        return false;
    }

    while(!input.eof())
    {
        std::string line;
        getline(input, line);
        if(line.size() > 18)
            return false;
        auto it = std::find_if(line.begin(), line.end(), NoDigitsAndSpace());
        if(it != line.end())
        {
            return false;
        }
    }
    return true;
}
