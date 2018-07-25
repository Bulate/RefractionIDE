#include "StandardInputOutputInspector.h"

#include <QAction>
#include <QTextEdit>
#include <QTextStream>
#include <QToolBar>
#include <QFile>

StandardInputOutputInspector::StandardInputOutputInspector(QWidget *parent)
	: QSplitter(parent)
{
	toolBar = new QToolBar("Options");
	toolBar->setOrientation(Qt::Vertical);
	setStretchFactor(1, 0);

	buildInspector();
}

void StandardInputOutputInspector::buildInspector()
{

	standardInputInspector = new QTextEdit();
    #ifdef Q_OS_MAC
    const int monospacedFontSize = 11;
    #else
    const int monospacedFontSize = 10;
    #endif
    // Set the default monospaced font of the game
    const QFont font ("Liberation Mono", monospacedFontSize);
    standardInputInspector->setFont(font);
	standardInputInspector->setReadOnly(true);
	standardInputInspector->setStyleSheet("background: rgb(222,222,255);");
	addWidget(standardInputInspector);

	userOutputInspector = new QTextEdit();
	userOutputInspector->setReadOnly(true);
	userOutputInspector->setStyleSheet("background: rgb(150,222,255);");
	addWidget(userOutputInspector);

	standarExpectedOutputInspector = new QTextEdit();
	standarExpectedOutputInspector->setReadOnly(true);
    standarExpectedOutputInspector->setFont(font);
	standarExpectedOutputInspector->setStyleSheet("background: rgb(222,255,222);");
	addWidget(standarExpectedOutputInspector);


}

void StandardInputOutputInspector::setInput(QFile* file)
{
	if ( file->open(QFile::ReadOnly) )
	{
		standardInputInspector->setPlainText(file->readAll());
	}

//	document()->setModified(false); // ToDo AVERIGUAR QUÉ HACE

}

void StandardInputOutputInspector::setOutput(QFile* file)
{
	if ( file->open(QFile::ReadOnly) )
	{
		standarExpectedOutputInspector->setPlainText(file->readAll());
	}

//	document()->setModified(false); // ToDo AVERIGUAR QUÉ HACE

}

void StandardInputOutputInspector::toggleOutputError()
{
	bool checked = toggleOutputErrorAction->isChecked();
    standarExpectedOutputInspector->setVisible( ! checked );
	standardErrorInspector->setVisible( checked );
}


