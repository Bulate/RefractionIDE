#include "MainWindow.h"
#include "CodeEditor.h"
#include "ResultsDockWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setObjectName("MainWindow"); // used to save preferences
    setWindowTitle("Refraction IDE");
    resize(1024, 768); // affects only desktop applications
    setMinimumSize(480, 320);
    codeEditor = new CodeEditor(this);
    setCentralWidget(codeEditor);
    resultsDockWidget = new ResultsDockWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea , resultsDockWidget);



}

MainWindow::~MainWindow()
{

}
