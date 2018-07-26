#ifndef STANDARDINPUTOUTPUTINSPECTOR_H
#define STANDARDINPUTOUTPUTINSPECTOR_H

#include <QSplitter>

//class PlayerSolution;

class QAction;
class QTextEdit;
class QToolBar;
class QFile;

class StandardInputOutputInspector : public QSplitter
{
	Q_OBJECT
	Q_DISABLE_COPY(StandardInputOutputInspector)

  protected:
	/// Shows test case's input text (black) and consumed input by player solution (grey)
	QTextEdit* standardInputInspector = nullptr;
	/// A toolbar in middle of the text editor with options
	QToolBar* toolBar = nullptr;
	/// Shows expected test case's standard output (grey) and player solution output. The latter
	/// is (black) when matches the former, or (red) otherwise
    QTextEdit* standardExpectedOutputInspector = nullptr;
	/// Compares the player solution error output against test case's expected standard error
    QTextEdit* standardProgramOutputInspector = nullptr;
	/// Toggles between standard output and standard error
	QAction* toggleOutputErrorAction = nullptr;
	/// We are visualizing input/output for this test case number
	int testCaseNumber = -1;

  public:
	/// Constructor
	explicit StandardInputOutputInspector(QWidget* parent = nullptr);
    /// Sets the input on the tab widget display
	void setInput(QFile* file);
    /// Sets the expected output on the tab widget display
    void setOutput(QFile* file);
    /// Sets a text program output on the tab widget display
    void setProgramOutput(QFile* file);
    /// Sets an HTML program output on the tab widget display
    void setProgramOutputHTML(QFile* file);


  protected:
	/// Builds the inspector with three areas
	void buildInspector();

  protected slots:
	/// Toggles between the standard output and standard error
	void toggleOutputError();

};

#endif // STANDARDINPUTOUTPUTINSPECTOR_H
