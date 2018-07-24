#include "PlayerSolution.h"

PlayerSolution::PlayerSolution(QObject *parent) : QObject(parent)
{

}

void PlayerSolution::addSolutionFile(QFile* value)
{
	userSolution = value;

}

void PlayerSolution::addInput(QFile* file)
{
	this->testCaseInputs.append(file);
}


void PlayerSolution::addOutput(QFile* file)
{
	this->testCaseInputs.append(file);
}
