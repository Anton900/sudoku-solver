#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <string>
#include <fstream>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QVector>
#include <QLineEdit>
#include <vector>
#include "cell.h"

using std::vector;

/*!
 * \brief The FileIO is the class for handling read and write operations for Sudoku files.
 */
class FileIO
{
public:
    /*!
     * \brief Default and parameterized constructor
     * \param path is the string for the filename to open
     */
    FileIO(QString path = "") :path(path) {}

    /*!
     * \brief Method to check that's it a valid sudoku file.
     * Lines can't be longer then 18 character and each character can only be a number between 0 - 9 and space (' ').
     * \return returns true if's valid
     */
    bool validSudokuFile();

    /*!
     * \brief Setter for path member variable
     * \param path to set from
     */

    void setPath(QString path);

    /*!
     * \brief Attempts to open the file from member variable 'path'.
     * \return returns true if file opening was successful, otherwise return false
     */
    bool openFile();
    /*!
     * \brief Read from the text file that's in the 'path' string variable
     *
     * Inserts the next value from the string to a integer. Create a cell object with that value and sets the coordinates and assigned to true or false. Continues until string is empty.
     *
     * \return returns the 2d vector container for the cells
     */
    vector<vector<Cell>> read();
    /*!
     * \brief Write to the text file that's in the 'path' string variable
     * \param grid is the container to extract the number contents from
     */
    void write(QVector<QVector<QLineEdit*>> puzzleGrid);

private:
    QString path;
    vector<vector<Cell>> grid;
};

/*!
 * \brief Function object to check it's only valid characters.
 * Only numbers between 0 - 9 and space (' ').
 */
struct NoDigitsAndSpace
{
    bool operator()(char c)
    {
        if(isdigit(c) || c == ' ')
        {
            if(isdigit(c))
            {
              int num = static_cast<int>(c);
              if(num >= 0 && num < 10)
                  return false;
            }
            return false;
        }
        return true;
    }
};

#endif
