#include "CodeEditor.h"

CodeEditor::CodeEditor(QWidget* parent)
    : QPlainTextEdit(parent)
//	, autoSaveTimer( new QTimer(this) )
//	, lineNumberArea( new LineNumberArea(this) )
{
    // Set the default monospaced font of the game
//	const QFont& font = BotNeumannApp::getMonospacedFont();
//	setFont(font);

//	// Make tabs the same size than 4 spaces
//	QFontMetrics metrics(font);
//	setTabStopWidth(tabStop * metrics.width(' '));

//	// Create the object that will provide color to C++ code within the editor
//	highlighter = new SyntaxHighlighter( document() );

//	// The idle timer always work in single shot basics
//	autoSaveTimer->setSingleShot(true);
//	autoSaveTimer->setInterval(autoSaveWait);
//	connect(autoSaveTimer, SIGNAL(timeout()), this, SLOT(saveChanges()));

//	// When user changes the number of lines on the editor, adjust the area of the line number
//	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));

//	// When this editor must be updated, because another window was covering it, or something else
//	// update the line number area widget too
//	connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));

//	// When user changes the cursor, highlight the active line and un-paint the old active one
//	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

//	// Calculate the initial line number area width
//	updateLineNumberAreaWidth();

//	// Make the first line as the the active one
//	highlightCurrentLine();
}
