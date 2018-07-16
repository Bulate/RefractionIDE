#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

///Foward declarations
class SyntaxHighlighter;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
    Q_DISABLE_COPY(CodeEditor)
protected:
    /// Store formatting rules for C++
    SyntaxHighlighter* highlighter;
public:
    /// Constructor
    explicit CodeEditor(QWidget* parent = nullptr);

};

#endif // CODEEDITOR_H
