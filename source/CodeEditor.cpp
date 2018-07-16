#include "CodeEditor.h"
#include "SyntaxHighlighter.h"
#include "LineNumberArea.h"
#include "Common.h"

#include <QPainter>


// A tab is visualized as 4 space characters
const int tabStop = 4; // characters

CodeEditor::CodeEditor(QWidget* parent)
    : QPlainTextEdit(parent)
//	, autoSaveTimer( new QTimer(this) )
    , lineNumberArea( new LineNumberArea(this) )
{
    // Set the default monospaced font of the game
    const QFont font ("Liberation Mono");
    setFont(font);

    // Make tabs the same size than 4 spaces
    QFontMetrics metrics(font);
    setTabStopWidth(tabStop * metrics.width(' '));

    // Create the object that will provide color to C++ code within the editor
    highlighter = new SyntaxHighlighter( document() );

//	// The idle timer always work in single shot basics
//	autoSaveTimer->setSingleShot(true);
//	autoSaveTimer->setInterval(autoSaveWait);
//	connect(autoSaveTimer, SIGNAL(timeout()), this, SLOT(saveChanges()));

    // When user changes the number of lines on the editor, adjust the area of the line number
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));

    // When this editor must be updated, because another window was covering it, or something else
    // update the line number area widget too
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));

//	// When user changes the cursor, highlight the active line and un-paint the old active one
//	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    // Calculate the initial line number area width
    updateLineNumberAreaWidth();

//	// Make the first line as the the active one
//	highlightCurrentLine();
}

void CodeEditor::updateLineNumberAreaWidth()
{
//    this->synchronizedWithObjectCode = false;
    // Make room in the left edge of the editor
    setViewportMargins(getLineNumberAreaWidth(), 0, 0, 0);
}



int CodeEditor::getLineNumberAreaWidth()
{
    // Get the number of lines currently displayed in the document
    // QPlainTextEdit uses the term block instead of line. If word wrap is enabled, a long line is
    // automatically sliced  and called a block (QTextBlock), compound of several virtual lines.
    int max = qMax(1, blockCount());

    // Count the digits required by that number
    int digits = digitsRequiredBy(max);

    // Calculate the maximum width in pixels of a digit
    int digitWidth = fontMetrics().width(QLatin1Char('9'));

    // The width in pixels of the line number area is the width of the last line number
    return digits * digitWidth;// + breakpointEdgeWidth;
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    // Painting the line number widget's background as ligth gray
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    // We are going to loop through all visible lines, start with the first one.
    // We get the top and bottom y-coordinate of the first text block
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    int lineNumberAreaWidth = getLineNumberAreaWidth();
    int fontHeight = fontMetrics().height() - 1;

    // Adjust these values by the height of the current text block in each iteration in the loop
    while (block.isValid() && top <= event->rect().bottom())
    {
        // Only update numbers for visible blocks, not for hidden blocks, even when they are hidded
        // by another window
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen( QColor(Qt::gray).darker() );
            // If this line has a breakpoint, paint it
//            paintBreakpoint(block, painter, top, lineNumberAreaWidth, fontHeight);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        // Move to the nex block (complete line)
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
