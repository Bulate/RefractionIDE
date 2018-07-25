﻿#include "MainWindow.h"
#include "CodeEditor.h"
#include "CodeSegment.h"
#include "ResultsDockWidget.h"
#include "PlayerSolution.h"

#include "Diagnostic.h"
#include <QLabel>
#include <iostream>
#include <QVBoxLayout>
#include "ToolCall/Compiler/Compiler.h"
#include <QDir>

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

}

void MainWindow::addCodeSegment()
{
    codeSegment = new CodeSeglogErrorsment(this);

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
    const QString& filepath = this->codeSegment->getFilePath();
    const QString test = this->codeSegment->getWorkingDirectory()->absolutePath() + QDir::separator() + "solution.out";
    const QFileInfo* route = new QFileInfo(test);

    //std::cerr << "Me cai" << filepath.toStdString() << "   |    " << route->filePath().toStdString();

    this->compiler = new Compiler(this);
    compiler->compile(filepath, *route );
    connect( this, SIGNAL(buildFinished()), this, SLOT(solutionBuildFinished()) );
    foreach (Diagnostic* diagnostic, compiler->getAllDiagnostics() )
        std::cout << " " << diagnostic;

}

void MainWindow::updateResultsDockWidfget(int testCasesCount
										  , const QList<QFile *> &testCaseInputs
										  , const QList<QFile *> &testCaseOutputs)
{
	resultsDockWidget->createTestCasesTabs(testCasesCount, testCaseInputs, testCaseOutputs);
}


bool MainWindow::solutionBuildFinished()
{
    return logErrors();
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

