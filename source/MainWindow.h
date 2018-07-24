#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declaration needed
class CodeEditor;
class CodeSegment;
class ResultsDockWidget;
class QLabel;
class QFile;


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
	QLabel *infoLabel;

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

	void addMenuFile();

	void createActions();
	void createMenus();

	void updateResultsDockWidfget(int testCasesCount
								  , const QList<QFile *>& testCaseInputs
								  , const QList<QFile *>& testCaseOutputs);

  protected slots:
    /// Compiles and runs
    void runSolution();




};

#endif // MAINWINDOW_H
