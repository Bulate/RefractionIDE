#ifndef CODESEGMENT_H
#define CODESEGMENT_H


#include <QDockWidget>
#include <QProcess>
#include <QFileInfo>
#include <QChar>
#include <QDir>

class CodeEditor;
//class Compiler;
//class CompiledProgram;
//class ExecutionThread;

class QFile;
class QAction;
class QComboBox;
class QTextStream;
class QMainWindow;
class QSlider;
class MainWindow;
class QDir;
//class Player;
class QProcess;
class PlayerSolution;
//class Unit;

class QMenu;
class ResultsDockWidget;

/**
    @brief Represents the data segment for the current unit.

    The data segment (this class) lists all the source files that compound the current's player
    solution, and let him/her to switch between them. The CodeEditor object is able to show and
    edit only one of these files at time. Therefore, this class deals with some source files at
    time, whereas CodeEditor must be notified when the current file has changed.
 */
class CodeSegment : public QDockWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(CodeSegment)

  protected: // General objects
    /// In order to have a toolbar, the widget of this code editor must be a main window
    QMainWindow* innerMainWindow;
    /// Object where the actual source code is shown and edited
    CodeEditor* codeEditor = nullptr;
// /// Manages the list of source files that compound the player's solution to an unit
    PlayerSolution* playerSolution = nullptr;
//	ResultsDockWidget* resultsDockWidget = nullptr;
    MainWindow* parentMainWindow;

  protected: // Edit toolbar
    /// Create new files in the solution: header file, source file and C++ classes
    QAction* openFolderAction;
    /// Undoes the last action done in the editor
    QAction* undoAction;
    /// Redoes the last undone action in the editor
    QAction* redoAction;
    /// Cuts the current selection in the text editor and places it into the clipboard
    QAction* cutAction;
    /// Copies the current selection in the text editor and places a copy into the clipboard
    QAction* copyAction;
    /// Paste a copy of the clipboard contents over the current selection in the text editor
    QAction* pasteAction;
    /// Save the progress on the document to the solution file
    QAction* saveAction;
    /// Stores the user selected working folder
    QDir* workingDirectory;
    /// Pointer to the user proces being executed
    QProcess* process;
    /// Stores wether each test case was passed or not
    QList<bool> testCaseState;


    /// Shows the option menu
    QMenu *fileMenu;
//    /// Let player change the file to be edited, if the solution is compound of several files
//    QComboBox* fileSelector;

  protected: // run menu options

    void createActions();
    void createMenus();


  protected: // Run toolbar
    /// Executes and animates the code or pauses it if already running
    QAction* runAction;
    /// If visualisation is paused, executes the next code statement in the current function
//    QAction* stepForwardAction;
//    /// Stops the visualisation of the code, if it is running
//    QAction* stopAction;
//    /// Allows user to set the speed of the visualization
//    QSlider* visualizationSpeedSlider;

  public:
    /// Constructor
    explicit CodeSegment(MainWindow *parent = nullptr, Qt::WindowFlags flags = 0);
    /// Destructor
  virtual ~CodeSegment();
    /// Get access to the code editor
//	inline CodeEditor* getCodeEditor() const { return codeEditor; }
    /// Restores the last code made by player for the given unit, or the default unit's code if
    /// player nas not played this unit
//  void loadPlayerCodeForUnit(PlayerSolution* playerSolution, Unit* unit);
    void setPointerToResults(ResultsDockWidget* resultsDockWidget);
    /// Getter for File Path atribute
    const QString& getFilePath();
    ///
    void runTestCase(QString solutionFile, QString inputfile, QString outputfile, bool isLastFile, const QList<QFile *> &expectedOutput, int index);
    long findFirstDiff(QFile &inputFile1, QFile &inputFile2, bool ignoreWhitespace, bool caseSensitive);
    QChar readNextChar(QTextStream& input, bool ignoreWhitespace, bool caseSensitive, bool eatWhitespace, long* position = nullptr);

    /// Rgetter method for the working directory attribute
    QDir *getWorkingDirectory() const;
    /// Runs the user solution against all of the test cases
    void runTestCases();

signals:
    /// Emitted when user presses the Run/Pause button
    void userRunOrPaused();


 protected:
    QAction* runOrPauseAction;
    /// Set up the inner main window
    void setupInnerWidget();
    /// Create standard editing tool bar with undo, copy, run, debug and other actions
    void setupEditingToolbar();
    /// Create a toolbar with buttons for running, stop, step into/out
    void setupRunToolbar();
    /// Create and configure the text editor object
    void setupCodeEditor();
    /// The Run and Pause share the same action for space constraints. This method converts the
    /// action in Run action
    /// @param name Send "Run" or "Resume"
    void setupRunAction(const QString& name, bool enabled);

    /// Gets the test cases information
    void getTestCaseInfo(QDir workingDirectory);
    ///Reads test cases
    void loadTestCases(QDir workingDirectory);
    /// Creates a solution QFile from a working Directory
    QFile* createSolutionFile(QDir& workingDirectory);

  protected slots:
    /// Called when the user calls to open a new folder to work with the editor.
    void openFolderTriggered();
	/// Called when the solution has been run, to display the result on screen
	void playerSolutionFinished(int exitCode, QProcess::ExitStatus exitStatus);
    /// Verifies if a test case is correct or not.
    void checkTestCase(QFile *programOutput, QFile *expectedOutput);

};

#endif // CODESEGMENT_H
