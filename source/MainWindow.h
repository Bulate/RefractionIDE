#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class CodeEditor;
class CodeSegment;
class ResultsDockWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    CodeEditor * codeEditor = nullptr;
    ResultsDockWidget *resultsDockWidget = nullptr;
    CodeSegment * codeSegment = nullptr;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


};

#endif // MAINWINDOW_H
