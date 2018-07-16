#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>



///Foward declarations
class SyntaxHighlighter;
class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
    Q_DISABLE_COPY(CodeEditor)
protected:
    /// Store formatting rules for C++
    SyntaxHighlighter* highlighter;
    /// Object that paints line numbers in the left margin of the code editor
    LineNumberArea* lineNumberArea;

public:
    /// Constructor
    explicit CodeEditor(QWidget* parent = nullptr);
    /// Calculate the width in pixels required by the line number area. The width depends on the
    /// number of lines of the current document
    int getLineNumberAreaWidth();
    /// When the line number area object must be painted, this method is called
    /// @remarks LineNumberArea class calls this method
    void lineNumberAreaPaintEvent(QPaintEvent* event);


protected slots:
    /// Make the left margin of the text editor bigger, in order to have space to the line number
    /// area widget
    void updateLineNumberAreaWidth();

};

#endif // CODEEDITOR_H
