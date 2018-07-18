#include "MainWindow.h"
#include "CodeEditor.h"
#include "CodeSegment.h"
#include "ResultsDockWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setUp();
    addCodeSegment();
    addResultDockWidget();
}

void MainWindow::MainWindow::setUp()
{
    // Used to save preferences
    setObjectName("MainWindow");
    setWindowTitle("Refraction IDE");

    resize(1024, 768); // affects only desktop applications
    setMinimumSize(480, 320);

}

void MainWindow::addCodeSegment()
{
    codeSegment = new CodeSegment(this);
    connect(codeSegment, &CodeSegment::userRunOrPaused, this, &MainWindow::runSolution);
    setCentralWidget(codeSegment);
}

void MainWindow::addResultDockWidget()
{
    resultsDockWidget = new ResultsDockWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea , resultsDockWidget);
}

void MainWindow::runSolution()
{

}


MainWindow::~MainWindow()
{

}

