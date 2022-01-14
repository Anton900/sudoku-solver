#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenu();
    sudokuWidget = new SudokuWidget();
    setWindowTitle(tr("Sudoku Solver"));
    this->setCentralWidget(sudokuWidget);
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open"), this);
    saveAction = new QAction(tr("&Save"), this);
    exitAction = new QAction(tr("&Exit"), this);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}
void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "C:/Files/Development/QT/SudokuQT/puzzles",
                                                    tr("Text Files (*.txt)"));
    fileIO.setPath(fileName);
    if (!fileIO.openFile())
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
    }
    else
    {
        if (!sudokuWidget->getGrid().empty())
            sudokuWidget->clearGrid();

        std::vector<std::vector<Cell>> grid = fileIO.read();
        sudokuWidget->updateDisplayGrid(grid);
        sudokuWidget->setGrid(grid);
    }
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    fileIO.setPath(fileName);
    fileIO.write(sudokuWidget->getCurrentDisplayGrid());
}

void MainWindow::quit()
{
    QMessageBox messageBox;
    messageBox.setWindowTitle(tr("SudokuGUI"));
    messageBox.setText(tr("Do you really want to quit?"));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);
    if (messageBox.exec() == QMessageBox::Yes)
        qApp->quit();
}
