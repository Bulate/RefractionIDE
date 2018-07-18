#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

///Foward declarations
class SyntaxHighlighter;
class LineNumberArea;

/**
 * @brief The CodeEditor class
 * that owns the code editor
 * part, here the user is able to edit
 * his solution, also set other things up
 * like the code highlighter
 */
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
    Q_DISABLE_COPY(CodeEditor)

 protected:
    /// Store formatting rules for C++
    SyntaxHighlighter* highlighter;
    /// Object that paints line numbers in the left margin of the code editor
    LineNumberArea* lineNumberArea;
    /// Overrided in order to adjust size of the line number area when the code editor is resize
    virtual void resizeEvent(QResizeEvent* event) override;

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
    /// @brief Invoked when the editor's viewport has been scrolled.
    /// In the editor we resize and draw the line numbers on the LineNumberArea. We need to do this
    /// when the number of lines in the editor changes, and when the editor's viewport() is scrolled
    /// @param rect The part of the editing area that is do be updated (redrawn).
    /// @param dy holds the number of pixels the view has been scrolled vertically.
    void updateLineNumberArea(const QRect& rect, int dy);
};

#endif // CODEEDITOR_H
