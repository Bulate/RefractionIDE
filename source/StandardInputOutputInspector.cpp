#include "StandardInputOutputInspector.h"

#include <QAction>
#include <QTextEdit>
#include <QTextStream>
#include <QToolBar>

StandardInputOutputInspector::StandardInputOutputInspector(QWidget *parent)
	: QSplitter(parent)
{
	buildInspector();
}

void StandardInputOutputInspector::buildInspector()
{
	standardInputInspector = new QTextEdit();
	standardInputInspector->setReadOnly(true);
	standardInputInspector->setStyleSheet("background: rgb(222,222,255);");
	addWidget(standardInputInspector);

	toolBar = new QToolBar("Options");
	toolBar->setOrientation(Qt::Vertical);
	setStretchFactor(1, 0);

    userOutputInspector = new QTextEdit();
    userOutputInspector->setReadOnly(true);
    userOutputInspector->setStyleSheet("background: rgb(150,222,255);");
    addWidget(userOutputInspector);

    standarExpectedOutputInspector = new QTextEdit();
    standarExpectedOutputInspector->setReadOnly(true);
    standarExpectedOutputInspector->setStyleSheet("background: rgb(222,255,222);");
    addWidget(standarExpectedOutputInspector);


}

void StandardInputOutputInspector::toggleOutputError()
{
	bool checked = toggleOutputErrorAction->isChecked();
    standarExpectedOutputInspector->setVisible( ! checked );
	standardErrorInspector->setVisible( checked );
}


