#ifndef USERSOLUTION_H
#define USERSOLUTION_H

#include <QObject>

class PlayerSolution : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PlayerSolution)

  protected:
    /// The number of available test cases for this player solution
    /// -1 means that test cases have not been generated
    int testCasesCount = -1;
    /// Counts the number of steps to have the entire player solution built and emit the
    /// @a allBuilt() signal
    int builtSteps = -1;
    /// Manages the process of building the executable from player solution's source code
//    CompiledProgram* playerSolutionProgram = nullptr;
//    /// The executable from a random selected Unit's solution
//    CompiledProgram* unitSolutionProgram = nullptr;
//    /// Object that generates the bn_tags.txt file with symbols extracted from source files
//    CtagsCall* ctagsCall = nullptr;


  public:
    explicit PlayerSolution(QObject *parent = nullptr);


signals:

public slots:
};

#endif // PLAYERSOLUTION_H
