#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfoList>

// Forward declaration needed
class CodeEditor;
class CodeSegment;
class ResultsDockWidget;
class QLabel;
class QFile;
class Compiler;
class QDir;

/**
 * @brief The MainWindow class
 * manages the main view of the user
 * that containts the code editor, the code
 * segment with the necessary tools, and also the
 * results dock widget that shows the test cases output/input
 * and shows the compiler output
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

  private:
    /// Pointers to each part of the main window
    CodeEditor * codeEditor = nullptr;
    ResultsDockWidget *resultsDockWidget = nullptr;
    CodeSegment * codeSegment = nullptr;
    Compiler* compiler = nullptr;
    QLabel *infoLabel;
    int errors = 0;

  public:
    /// Constructor
    MainWindow(QWidget *parent = nullptr);
    /// Destructor
    ~MainWindow();
    /// Set up some preferences on the main window
    void setUp();
    /// Add the code segment to the central widget
    void addCodeSegment();
    /// Adds the result dock widget to the window
    void addResultDockWidget();
    /// ToDo Add file menu
    void addMenuFile();

    /// ToDo create actions
    void createActions();
    /// TODO Create menus
    void createMenus();
    /// Calls the update of a results dock widget.
    void updateResultsDockWidfget(int testCasesCount
                                  , const QList<QFile *>& testCaseInputs
                                  , const QList<QFile *>& testCaseOutputs
                                  , const QList<QFile *>& testProgramOutputs
                                  , const QList<bool> testCaseState
                                  , const QFileInfoList &inputInfoList
                                  , const QFileInfoList &outputInfoList
                                  , const QFileInfoList &programOutputInfoList
                                  , const QDir workingDirectory);

  protected slots:
    /// Compiles and runs
    void runSolution();
    /// Displays the errors from the compiler on the compiler output tab
    void printError();
    /// Runs the player solution against all of the test cases
    void runTestCases();




};

#endif // MAINWINDOW_H
