#include "CodeEditor.h"
#include "CodeSegment.h"
#include <iostream>
// #include "CompiledProgram.h"     IMPORTANTE HACER LA IMPLEMENTACION
// #include "Compiler.h"
//#include "Diagnostic.h"
//#include "ExecutionThread.h"
//#include "LogManager.h"
#include "PlayerSolution.h"
#include "ResultsDockWidget.h"
//#include "Unit.h"
//#include "VisualizationContext.h"
//#include "VisualizationSpeed.h"
#include <QProcess>
#include <QAction>
#include <QComboBox>
#include <QMainWindow>
#include <QSlider>
#include <QTextStream>
#include <QToolBar>
#include <QString>
#include <QFileDialog>
#include <iostream>
#include <string>
#include "MainWindow.h"

// Default width and height of the tools in toolbars
const int toolBarIconSize = 18;

QDir *CodeSegment::getWorkingDirectory() const
{
    return workingDirectory;
}

void CodeSegment::runTestCases()
{
    QString solutionFile = this->getWorkingDirectory()->absolutePath() + QDir::separator() +"solution.out" ;
    QFileInfoList inputs = playerSolution->getInputInfo();
    // Create a tester for each test case and run the test case
    for ( int index = 0; index < inputs.size(); ++index )
    {
        QString inputFile = inputs.at(index).absoluteFilePath();
        QString outputFilePath;
        outputFilePath.sprintf("%s%c%s%03d%s", this->getWorkingDirectory()->absolutePath().toStdString().c_str(), QDir::separator().toLatin1() , "p_output" , index+1 , ".txt");
        //std::cerr << outputFilePath.toStdString();
        QFileInfo* outputFile = new QFileInfo( outputFilePath);
        playerSolution->addProgramOutputInfo(*outputFile);
        runTestCase( solutionFile, inputFile , outputFile->absoluteFilePath(), (index == inputs.size()-1), playerSolution->getTestCaseOutputs(), index);
    }
}

void CodeSegment::runTestCase(QString solutionFile, QString inputfile, QString outputfile, bool isLastFile, const QList<QFile *> &expectedOutput, int index)
{

    // Create an object to call the user executable
    QProcess* process = new QProcess(this);

	if(isLastFile)
		connect( process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(playerSolutionFinished(int,QProcess::ExitStatus)) );

    // Call the player solution
    process->setReadChannelMode(QProcess::SeparateChannels);
    process->setStandardInputFile( inputfile );
    process->setStandardOutputFile( outputfile );
    process->start( solutionFile );
}

CodeSegment::CodeSegment(MainWindow* parent, Qt::WindowFlags flags)
    : QDockWidget(tr("Program Options"), parent, flags)
    , innerMainWindow( new QMainWindow(this))
    , parentMainWindow(parent)
{
    setObjectName("codeSegment");
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    setupInnerWidget();
    setupCodeEditor(); // It must be called before the toolbars
    setupEditingToolbar();
    innerMainWindow->addToolBarBreak();
    setupRunToolbar();
}

CodeSegment::~CodeSegment()
{
}

void CodeSegment::setupInnerWidget()
{
    // Ask the main window to behave as normal widget, instead of a real main window
    innerMainWindow->setWindowFlags(Qt::Widget);

    // Set the inner main window as the inner widget of this dock widget
    setWidget(innerMainWindow);
}

void CodeSegment::setupEditingToolbar()
{
    // Create the toolbar
    QToolBar* editToolBar = innerMainWindow->addToolBar(tr("Edit"));
    editToolBar->setIconSize( QSize(toolBarIconSize, toolBarIconSize) );

    // Opens a new file in the solution
    openFolderAction = new QAction(QIcon(":/unit_playing/buttons/new_file.svg"), tr("&Open Folder"), this);
    openFolderAction->setObjectName("openFolder");
    openFolderAction->setShortcut(QKeySequence("Ctrl+N"));
    openFolderAction->setStatusTip(tr("Opens a folder to work with the editor"));
    connect(openFolderAction, SIGNAL(triggered()), this, SLOT(openFolderTriggered()));
    editToolBar->addAction(openFolderAction);


    // Save file in the solution
    saveAction = new QAction(QIcon(":/unit_playing/buttons/save.svg"), tr("&Save File"), this);
    saveAction->setObjectName("save");
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    saveAction->setStatusTip(tr("save file"));
    connect(codeEditor, SIGNAL(undoAvailable(bool)), saveAction, SLOT(setEnabled(bool)));
    connect(saveAction, SIGNAL(triggered()), codeEditor, SLOT(save()));
    editToolBar->addAction(saveAction);


    // Undo
    undoAction = new QAction(QIcon(":/unit_playing/buttons/undo.svg"), tr("&Undo"), this);
    undoAction->setObjectName("undo");
    undoAction->setEnabled(false);
    undoAction->setShortcut(QKeySequence("Ctrl+Z"));
    undoAction->setStatusTip(tr("Undoes the last action done in the editor"));
    connect(codeEditor, SIGNAL(undoAvailable(bool)), undoAction, SLOT(setEnabled(bool)));
    connect(undoAction, SIGNAL(triggered()), codeEditor, SLOT(undo()));
    editToolBar->addAction(undoAction);

    // Redo
    redoAction = new QAction(QIcon(":/unit_playing/buttons/redo.svg"), tr("&Redo"), this);
    redoAction->setObjectName("redo");
    redoAction->setEnabled(false);
    redoAction->setShortcut(QKeySequence("Ctrl+Shift+Z"));
    redoAction->setStatusTip(tr("Redoes the last undone action in the editor"));
    connect(codeEditor, SIGNAL(redoAvailable(bool)), redoAction, SLOT(setEnabled(bool)));
    connect(redoAction, SIGNAL(triggered()), codeEditor, SLOT(redo()));
    editToolBar->addAction(redoAction);

    // Cut
    cutAction = new QAction(QIcon(":/unit_playing/buttons/cut.svg"), tr("C&ut"), this);
    cutAction->setObjectName("cut");
    cutAction->setEnabled(false);
    cutAction->setShortcut(QKeySequence("Ctrl+X"));
    cutAction->setStatusTip(tr("Moves the selection to the clipboard"));
    connect(codeEditor, SIGNAL(copyAvailable(bool)), cutAction, SLOT(setEnabled(bool)));
    connect(cutAction, SIGNAL(triggered()), codeEditor, SLOT(cut()));
    editToolBar->addAction(cutAction);

    // Copy
    copyAction = new QAction(QIcon(":/unit_playing/buttons/copy.svg"), tr("&Copy"), this);
    copyAction->setObjectName("copy");
    copyAction->setEnabled(false);
    copyAction->setShortcut(QKeySequence("Ctrl+C"));
    copyAction->setStatusTip(tr("Copies the selection to the clipboard"));
    connect(codeEditor, SIGNAL(copyAvailable(bool)), copyAction, SLOT(setEnabled(bool)));
    connect(copyAction, SIGNAL(triggered()), codeEditor, SLOT(copy()));
    editToolBar->addAction(copyAction);

    // Paste
    pasteAction = new QAction(QIcon(":/unit_playing/buttons/paste.svg"), tr("&Paste"), this);
    pasteAction->setObjectName("paste");
    pasteAction->setEnabled(false);
    pasteAction->setShortcut(QKeySequence("Ctrl+V"));
    pasteAction->setStatusTip(tr("Pastes the clipboard contents over the selection"));

    connect(codeEditor, SIGNAL(undoAvailable(bool) ), pasteAction, SLOT(setEnabled(bool)));
    connect(pasteAction, SIGNAL(triggered()), codeEditor, SLOT(paste()));
    editToolBar->addAction(pasteAction);

//    // A combo box to show and choose the active file being edited
//    fileSelector = new QComboBox();
//    connect(fileSelector, SIGNAL(currentIndexChanged(QString)), this, SLOT(fileSelectorIndexChanged(QString)));
//    editToolBar->addWidget(fileSelector);

    innerMainWindow->addToolBar(editToolBar);
   // setWidget(editToolBar);

}


void CodeSegment::setupRunToolbar()
{
    // Create the toolbar
    QToolBar* toolBar = innerMainWindow->addToolBar(tr("Run"));
    toolBar->setIconSize( QSize(toolBarIconSize, toolBarIconSize) );

    // Create the Run action
    runAction = new QAction(QIcon(":/unit_playing/buttons/run.svg"), tr("R&un"), this);
    setupRunAction("Run", false);
    runAction->setShortcut(QKeySequence("Ctrl+R"));
    runAction->setEnabled(true);

     //  setupRunAction("Run", false);
    connect(runAction, &QAction::triggered, this, &CodeSegment::userRunOrPaused  );
    toolBar->addAction(runAction);

    innerMainWindow->addToolBar(toolBar);

}




void CodeSegment::setupCodeEditor()
{
    // ToDo: Have several code editors, one for each source file in player's solution
    // The code editor is a QTextEdit object
    codeEditor = new CodeEditor(this);

//	// Propagate events to the visualization controller and the debugger
    //connect( codeEditor, SIGNAL(breakpointAction(GuiBreakpoint*)), this, SIGNAL(breakpointAction(GuiBreakpoint*)) );

    // Place the code editor as the central widget of this dock widget
    innerMainWindow->setCentralWidget(codeEditor);


    // Do not force users to click the editor in order to start typing on it
    codeEditor->setFocus();
}

void CodeSegment::setupRunAction(const QString& name, bool enabled)
{
    runOrPauseAction = new QAction(this);

    runOrPauseAction->setObjectName(name);
    runOrPauseAction->setIcon( QIcon(":/unit_playing/buttons/run.svg") );
    runOrPauseAction->setToolTip(name == "Run" ? tr("Run: compiles the code and starts the visualization (Ctrl+R)") : tr("Resumes the visualization (Ctrl+R)"));
    runOrPauseAction->setShortcut(QKeySequence("Ctrl+R"));

    runOrPauseAction->setEnabled(enabled);
}





void CodeSegment::openFolderTriggered()
{
    // Send parent to new dialog
    this->workingDirectory = new QDir(QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath()));
    QFile* tempSolution = createSolutionFile(*workingDirectory);
    this->playerSolution = new PlayerSolution(this);
    this->playerSolution->addSolutionFile(tempSolution);
    this->codeEditor->loadFileContents(tempSolution);
    this->getTestCaseInfo(*workingDirectory);
//	connect(openFolderAction, SIGNAL(triggered()), parentMainWindow, SIGNAL(updateResultsDockWidfget())  );
//	this->resultsDockWidget->createTestCasesTabs();

}

void CodeSegment::playerSolutionFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	Q_UNUSED(exitCode);
	Q_UNUSED(exitStatus);    
    this->loadTestCases(*workingDirectory);
}

void CodeSegment::checkTestCase(QFile* programOutput, QFile* expectedOutput)
{
    long firstDiff = this->findFirstDiff(*programOutput, *expectedOutput, true, true);
    this->testCaseState.push_back(firstDiff == -1);
    //std::cerr << "[" << firstDiff << "]"<< std::endl;
}

void CodeSegment::setPointerToResults(ResultsDockWidget* resultsDockWidget)
{
    (void) resultsDockWidget;
}

const QString &CodeSegment::getFilePath()
{
    return this->codeEditor->filepath;
}


void CodeSegment::getTestCaseInfo(QDir workingDirectory)
{
	QFileInfo* tempInputInfo;
	QFileInfo* tempOutputInfo;
    int count = 1;
    do
    {
        QString inputName;
        inputName.sprintf("%s%03d%s", "input", count, ".txt");
        QString* inputPath = new QString(workingDirectory.filePath(inputName));
		tempInputInfo = new QFileInfo(*inputPath);

		QString outputName;
		outputName.sprintf("%s%03d%s", "output", count, ".txt");
		QString* outputPath = new QString(workingDirectory.filePath(outputName));
		tempOutputInfo = new QFileInfo(*outputPath);

		if (tempInputInfo->exists() && tempOutputInfo->exists())
        {
			this->playerSolution->addInputInfo(*tempInputInfo);
			this->playerSolution->addOutputInfo(*tempOutputInfo);
        }

        ++count;
	}while (tempInputInfo->exists());
}
void CodeSegment::loadTestCases(QDir workingDirectory)
{
    QFile* tempTestCaseInput ;
    QFile* tempTestCaseOutput;
    QFile* tempProgramOutput;
    ///  Dp while there are test cases to load
    int count = 1;
    do
    {
        QString inputName;
        inputName.sprintf("%s%03d%s", "input", count, ".txt");
        QString* inputPath = new QString(workingDirectory.filePath(inputName));

        QString outputName;
        outputName.sprintf("%s%03d%s", "output", count, ".txt");
        QString* outputPath = new QString(workingDirectory.filePath(outputName));

        QString pOutputName;
        pOutputName.sprintf("%s%03d%s", "p_output", count, ".txt");
        QString* pOutputPath = new QString(workingDirectory.filePath(pOutputName));

        //std::cerr<<tempPath->toStdString()
        tempTestCaseInput = new QFile(*inputPath);
        tempTestCaseOutput = new QFile(*outputPath);
        tempProgramOutput = new QFile(*pOutputPath);

        if (tempTestCaseInput->exists() && tempTestCaseOutput->exists() && tempProgramOutput->exists())
        {
            //codeEditor->filepath = *inputPath;
            this->playerSolution->addInput(tempTestCaseInput);
            this->playerSolution->addOutput(tempTestCaseOutput);
            this->playerSolution->addProgramOutput(tempProgramOutput);
            checkTestCase(tempTestCaseOutput, tempProgramOutput);
//			std::cerr << "Me lei" ;
        }

        ++count;
    } while (tempTestCaseInput->exists());


    this->parentMainWindow->updateResultsDockWidfget(playerSolution->getTestCasesCount()
													 , playerSolution->getTestCaseInputs()
                                                     , playerSolution->getTestCaseOutputs()
                                                     , playerSolution->getProgramOutputs()
													 , this->testCaseState
													 , playerSolution->getOutputInfo()
													 , playerSolution->getProgramOutputsInfo()
													 , workingDirectory );


}
QFile* CodeSegment::createSolutionFile(QDir& workingDirectory)
{
   // Try for all the supported Solution names
    const char* const solutionNames [] = {"solution.cpp", "Solution.cpp", "solution.c", "Solution.c"};
    for(int count = 0; count < 4; ++count)
    {
        QFile* tempSolution = new QFile(workingDirectory.filePath(solutionNames[count]));
        QString* tempPath = new QString(workingDirectory.filePath(solutionNames[count]));
        if(tempSolution->exists())
        {
            codeEditor->filepath = *tempPath;
            return tempSolution;
        }
    }
    return new QFile();
}


//void CodeSegment::fileSelectorIndexChanged(const QString& text)
//{
//	// Get the full path to the filename and load it in the code editor
//	codeEditor->loadFile( playerSolution->getPlayerUnitSourcePath(text) );
//}


long CodeSegment::findFirstDiff(QFile& inputFile1, QFile& inputFile2, bool ignoreWhitespace, bool caseSensitive)
{
    if ( inputFile1.open(QIODevice::ReadOnly | QIODevice::Text) == false )
    {
        inputFile1.close();
        return -2;
    }
    if ( inputFile2.open(QIODevice::ReadOnly | QIODevice::Text) == false )
    {
        inputFile1.close();
        inputFile2.close();
        return -2;
    }

    // If both files are empty, they match

    if ( inputFile1.atEnd() || inputFile2.atEnd() )
    {
        inputFile1.close();
        inputFile2.close();
        return -1;
    }

    // At least one file has data, we have to read them to compare
    QTextStream inputText1(&inputFile1);
    QTextStream inputText2(&inputFile2);

    // Used to know the current position in files
    long position1 = 0;
    QChar ch1 = 0;
    QChar ch2 = 0;

    // Read until reaching the first EOF
    while ( ! inputText1.atEnd() )
    {
        if ( inputText2.atEnd() )
        {
            inputFile1.close();
            inputFile2.close();
            return position1;
        }

        // Get the next char of each file
        ch1 = readNextChar(inputText1, ignoreWhitespace, caseSensitive, ch1 == ' ', &position1);
        ch2 = readNextChar(inputText2, ignoreWhitespace, caseSensitive, ch2 == ' ');

        // Compare the next character of each file
        if ( ch1 != ch2 )
        {
            inputFile1.close();
            inputFile2.close();
            return position1;
        }

        // Both files are identical until this char, continue
    }

    // If there is remaining expected information that player did not produced, fail
    if ( ! inputFile2.atEnd() )
    {
        inputFile1.close();
        inputFile2.close();
        return position1;
    }

    // We did not find any difference
    inputFile1.close();
    inputFile2.close();
    return -1;
}

QChar CodeSegment::readNextChar(QTextStream& input, bool ignoreWhitespace, bool caseSensitive, bool eatWhitespace, long* position)
{
    // Read the next character
    QChar ch = -1;

    // We may need to repeat when ignoring whitespace
    while ( ! input.atEnd() )
    {
        // Read the character
        input >> ch;

        // We have read a character, advance the position counter
        if ( position )
            ++(*position);

        // If we have to ignore case, we convert all characters to lowercase
        if ( caseSensitive == false )
            ch = ch.toLower();

        // If we got a non space character, we have found the next character
        if ( ! ch.isSpace() )
            return ch;

        // We found a whitespace character, if they must be match exact, return it
        if ( ! ignoreWhitespace )
            return ch;

        // We found a whitespace character and are ignoring them, uniform them to spaces
        ch = ' ';

        // If asked to eat whitespaces, we continue the while, otherwise we stop here
        if ( ! eatWhitespace )
            return ch;
    }

    return ch;
}

