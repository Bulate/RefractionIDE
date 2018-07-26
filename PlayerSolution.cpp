#include "PlayerSolution.h"
#include <QFileInfoList>
#include <QFileInfo>


int PlayerSolution::getTestCasesCount() const
{
	return testCasesCount;
}

void PlayerSolution::setTestCasesCount(int value)
{
	testCasesCount = value;
}

QList<QFile *> PlayerSolution::getTestCaseInputs() const
{
	return testCaseInputs;
}

QList<QFile *> PlayerSolution::getTestCaseOutputs() const
{
	return testCaseOutputs;
}

QFileInfoList PlayerSolution::getInputInfo() const
{
    return inputInfo;
}


QFileInfoList PlayerSolution::getOutputInfo() const
{
	return outputInfo;
}

QFileInfoList PlayerSolution::getProgramOutputsInfo() const
{
    return programOutputsInfo;
}

QList<QFile *> PlayerSolution::getProgramOutputs() const
{
    return programOutputs;
}



PlayerSolution::PlayerSolution(QObject *parent) : QObject(parent)
{

}

void PlayerSolution::addSolutionFile(QFile* value)
{
	userSolution = value;

}

void PlayerSolution::addInput(QFile* file)
{
	this->testCasesCount++;
    this->testCaseInputs.append(file);
}

void PlayerSolution::addInputInfo(QFileInfo info)
{
    this->inputInfo.append(info);
}

void PlayerSolution::addOutputInfo(QFileInfo info)
{
	this->outputInfo.append(info);
}

void PlayerSolution::addOutput(QFile* file)
{
    this->testCaseOutputs.append(file);
}
void PlayerSolution::addProgramOutput(QFile* file)
{
    this->programOutputs.append(file);
}

void PlayerSolution::addProgramOutputInfo(QFileInfo info)
{
    this->programOutputsInfo.append(info);
}
