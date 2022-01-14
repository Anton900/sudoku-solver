#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include "sudokuwidget.h"
#include "fileio.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class is to display the main window application.
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief Function to create the actions for the menu
     */
    void createActions();
    /*!
     * \brief createMenu
     */
    void createMenu();

    ~MainWindow();

private slots:
    /*!
     * \brief The slot to open and load a file.
     *
     * If file exists and writeable, remove current grid (if there's one) and load new grid from file.
     *
     */
    void open();
    /*!
     * \brief The slot to save grid to file.
     *
     * If file is exists and writeable, write grid to the file.
     *
     */
    void save();
    /*!
     * \brief The quit slot to quit the application.
     *
     * Open a QMessageBox for confirmation and if user clicks yes then quit application.
     *
     */
    void quit();

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    SudokuWidget *sudokuWidget;

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    FileIO fileIO;

};
#endif // MAINWINDOW_H
