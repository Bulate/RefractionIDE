#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>


class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
    Q_DISABLE_COPY(CodeEditor)

public:
    /// Constructor
    explicit CodeEditor(QWidget* parent = nullptr);

};

#endif // CODEEDITOR_H
