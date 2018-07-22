#include "MainWindow.h"
#include "CodeEditor.h"
#include "CodeSegment.h"
#include "ResultsDockWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setUp();
    addCodeSegment();
    addResultDockWidget();
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
    codeSegment = new CodeSegment(this);
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

}

void MainWindow::addMenuFile()
{
	QWidget *widget = new QWidget;
	setCentralWidget(widget);

	QWidget *topFiller = new QWidget;
	topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//	infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
//							  "invoke a context menu</i>"));
//	infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
//	infoLabel->setAlignment(Qt::AlignCenter);

	QWidget *bottomFiller = new QWidget;
	bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//	QVBoxLayout *layout = new QVBoxLayout;
//	layout->setMargin(5);
//	layout->addWidget(topFiller);
//	layout->addWidget(infoLabel);
//	layout->addWidget(bottomFiller);
//	widget->setLayout(layout);
}

MainWindow::~MainWindow()
{

}

