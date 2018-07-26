#include "MainWindow.h"
#include "CodeEditor.h"
#include "CodeSegment.h"
#include "ResultsDockWidget.h"
#include "PlayerSolution.h"
#include <QLabel>
#include <iostream>
#include <QVBoxLayout>
#include "ToolCall/Compiler/Compiler.h"
#include <QDir>
#include "ToolCall/Compiler/Diagnostic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setUp();
    addResultDockWidget();
    addCodeSegment();
    addMenuFile();

}

void MainWindow::MainWindow::setUp()
{
    // Used to save preferences
    setObjectName("MainWindow");
    setWindowTitle("Refraction IDE");

    resize(1024, 768); // affects only desktop applications
    setMinimumSize(480, 320);
#ifdef Q_OS_LINUX
    setWindowIcon(QIcon(":/IDELogo.svg"));
#endif

}

void MainWindow::addCodeSegment()
{
    codeSegment = new CodeSegment(this);

    codeSegment->setPointerToResults(this->resultsDockWidget);

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
    this->resultsDockWidget->clear();
    const QString& filepath = this->codeSegment->getFilePath();
    const QString test = this->codeSegment->getWorkingDirectory()->absolutePath() + QDir::separator() + "solution.out";
    const QFileInfo* route = new QFileInfo(test);

//    std::cerr << "Me cai" << filepath.toStdString() << "   |    " << route->filePath().toStdString();

    this->compiler = new Compiler(this);
    compiler->compile(filepath, *route );


    connect (compiler, &Compiler::finished, this, &MainWindow::printError );
    connect(compiler, &Compiler::finished, this, &MainWindow::runTestCases);
}

void MainWindow::printError()
{
    QList<Diagnostic* > diagnostic = compiler->getAllDiagnostics();

    for (auto index = diagnostic.cbegin(); index < diagnostic.cend(); index++)
    {
        std::cout << "Entre  " << index.operator*()->getBrief().toStdString();
        this->resultsDockWidget->appendDiagnostic(index.operator*());
    }
    this->errors = compiler->getErrorCount();
    this->compiler->clear();
    this->compiler = nullptr;

}

void MainWindow::runTestCases()
{
    if(errors == 0)
        codeSegment->runTestCases();
}




void MainWindow::updateResultsDockWidfget(int testCasesCount
										  , const QList<QFile *> &testCaseInputs
										  , const QList<QFile *> &testCaseOutputs
										  , const QList<QFile *> &testProgramOutputs
										  , const QList<bool> testCaseState
                                          , const QFileInfoList &inputInfoList
										  , const QFileInfoList &outputInfoList
										  , const QFileInfoList &programOutputInfoList
										  , const QDir workingDirectory)

{
    resultsDockWidget->createTestCasesTabs(testCasesCount, testCaseInputs, testCaseOutputs, testProgramOutputs, testCaseState, inputInfoList, outputInfoList, programOutputInfoList, workingDirectory);
}

void MainWindow::addMenuFile()
{
//	QWidget *topFiller = new QWidget;
//	topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//	infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
//							  "invoke a context menu</i>"));
//	infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
//	infoLabel->setAlignment(Qt::AlignCenter);

//	QWidget *bottomFiller = new QWidget;
//	bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//	QVBoxLayout *layout = new QVBoxLayout;
//	layout->setMargin(5);
//	layout->addWidget(topFiller);
//	layout->addWidget(infoLabel);
//	layout->addWidget(bottomFiller);
//	setLayout(layout);

}
void MainWindow::createActions()
{

}
void MainWindow::createMenus()
{}


MainWindow::~MainWindow()
{

}

