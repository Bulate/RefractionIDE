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
	standardInputInspector->setStyleSheet("background: rgb(255,255,153);");
	addWidget(standardInputInspector);

    standardExpectedOutputInspector = new QTextEdit();
    standardExpectedOutputInspector->setReadOnly(true);
    standardExpectedOutputInspector->setFont(font);
    standardExpectedOutputInspector->setStyleSheet("background: rgb(153,204,255);");
    addWidget(standardExpectedOutputInspector);

    standardProgramOutputInspector = new QTextEdit();
    standardProgramOutputInspector->setReadOnly(true);
    standardProgramOutputInspector->setFont(font);
    standardProgramOutputInspector->setStyleSheet("background: rgb(150,222,255);");
    addWidget(standardProgramOutputInspector);
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
        standardExpectedOutputInspector->setPlainText(file->readAll());
	}

//	document()->setModified(false); // ToDo AVERIGUAR QUÉ HACE

}

void StandardInputOutputInspector::setProgramOutput(QFile* file)
{
    if ( file->open(QFile::ReadOnly) )
    {
        standardProgramOutputInspector->setPlainText(file->readAll());
    }

//	document()->setModified(false); // ToDo AVERIGUAR QUÉ HACE

}

void StandardInputOutputInspector::setProgramOutputHTML(QFile* file)
{
    if ( file->open(QFile::ReadOnly) )
    {
        standardProgramOutputInspector->setHtml(file->readAll());
    }

    //	document()->setModified(false); // ToDo AVERIGUAR QUÉ HACE

}

void StandardInputOutputInspector::toggleOutputError()
{
	bool checked = toggleOutputErrorAction->isChecked();
    standardExpectedOutputInspector->setVisible( ! checked );
    standardProgramOutputInspector->setVisible( checked );
}


