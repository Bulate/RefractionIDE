#include "PlayerSolution.h"

PlayerSolution::PlayerSolution(QObject *parent) : QObject(parent)
{

}

void PlayerSolution::addSolutionFile(QFile* value)
{
	userSolution = value;

}
