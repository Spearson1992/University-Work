#include "GameLogic.h"
//#include "PhysicsEngine.h"

namespace Game
{
	GameLogic::GameLogic()
		:score(0), lives(3), isMultiball(false), isGameOver(false), ballReset(false), multiBallsRemaining(0){}

	void GameLogic::GameOver()
	{
		isGameOver = true;
	}

	
	
}