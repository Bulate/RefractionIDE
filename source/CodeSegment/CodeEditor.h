#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

///Foward declarations
class SyntaxHighlighter;
class LineNumberArea;
class QFile;
class QTimer;


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
	/// Fires a short time after the last made change in the document, in order to do some tasks
	/// such as auto save() and auto compile()
	QTimer* autoSaveTimer;
	/// Saves the text cursor before starting the animation. It will recovered when it is finished
	QTextCursor savedCursor;

 public:
    /// Constructor
	explicit CodeEditor(QWidget* parent = nullptr);
	/// The full path to the source file being edited
	QString filepath;
	/// Calculate the width in pixels required by the line number area. The width depends on the
    /// number of lines of the current document
    int getLineNumberAreaWidth();
    /// When the line number area object must be painted, this method is called
    /// @remarks LineNumberArea class calls this method
    void lineNumberAreaPaintEvent(QPaintEvent* event);
    /// Gets all of the text contained in one file and displays it on the Text Editor
	bool loadFileContents(QFile* file);



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
	/// Saves if there are changes to the @a filepath document in secondary memory
	/// @return true on success or when there is not need to save, false on error
	bool saveChanges();

protected slots:
  /// Called each time the document is changed
  void documentChanged();
  /// Saves always the content of editor to the @a filepath document in secondary memory
  /// @return true on success, false on error
  bool save();
};

#endif // CODEEDITOR_H
