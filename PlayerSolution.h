#ifndef PLAYERSOLUTION_H
#define PLAYERSOLUTION_H

#include <QObject>
#include <QFileInfoList>
class QFile;



class PlayerSolution : public QObject
{
    Q_OBJECT
	Q_DISABLE_COPY(PlayerSolution)

  protected:
	/// The number of available test cases for this player solution
	/// -1 means that test cases have not been generated
	 int testCasesCount = 0;
	/// Counts the number of steps to have the entire player solution built and emit the
    /// @a allBuilt() signal
    int builtSteps = -1;
    /// Manages the process of building the executable from player solution's source code
	/// This file contains the solution provided by the user
	QFile* userSolution;
	/// Stores the test cases
	QList<QFile*> testCaseInputs;
    QFileInfoList inputInfo;
	QList<QFile*> testCaseOutputs;
    QFileInfoList programOutputs;

	/// The number of available test cases for this player solution
	/// -1 means that test cases have not been generated
//	int testCasesCount = -1;

//    CompiledProgram* playerSolutionProgram = nullptr;
//    /// The executable from a random selected Unit's solution
//    CompiledProgram* unitSolutionProgram = nullptr;
//    /// Object that generates the bn_tags.txt file with symbols extracted from source files
//    CtagsCall* ctagsCall = nullptr;


  public:
	explicit PlayerSolution(QObject *parent = nullptr);
	void addSolutionFile(QFile* value);
	void addInput(QFile* file);
    void addInputInfo(QFileInfo info);
	void addOutput(QFile* file);
    void addProgramOutput(QFileInfo info);

	int getBuiltSteps() const;
	void setBuiltSteps(int value);

	int getTestCasesCount() const;

	void setTestCasesCount(int value);

	QList<QFile *> getTestCaseInputs() const;

	QList<QFile *> getTestCaseOutputs() const;

    QFileInfoList getInputInfo() const;

    QFileInfoList getProgramOutputs() const;

signals:

public slots:
};

#endif // PLAYERSOLUTION_H
