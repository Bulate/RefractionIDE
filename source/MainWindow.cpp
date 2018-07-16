#include "MainWindow.h"
#include "CodeEditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setObjectName("MainWindow"); // used to save preferences
    setWindowTitle("Refraction IDE");
    resize(1024, 768); // affects only desktop applications
    setMinimumSize(480, 320);
    codeEditor = new CodeEditor(this);
    setCentralWidget(codeEditor);
}

MainWindow::~MainWindow()
{

}
