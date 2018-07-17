#include "MainWindow.h"
#include "CodeEditor.h"
#include "CodeSegment.h"
#include "ResultsDockWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setObjectName("MainWindow"); // used to save preferences
    setWindowTitle("Refraction IDE");
    resize(1024, 768); // affects only desktop applications
    setMinimumSize(480, 320);
//    codeEditor = new CodeEditor(this);
    codeSegment = new CodeSegment(this);
//    setCentralWidget(codeEditor);
    resultsDockWidget = new ResultsDockWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea , resultsDockWidget);
    addDockWidget(Qt::TopDockWidgetArea , codeSegment);



}

MainWindow::~MainWindow()
{

}
