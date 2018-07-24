#include "PlayerSolution.h"



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


void PlayerSolution::addOutput(QFile* file)
{
	this->testCaseOutputs.append(file);
}
