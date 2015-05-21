
#include "SimulationCallback.h"
#include "Externals.h"
#include <iomanip>
#include <iostream>

namespace PhysicsEngine
{
///Method called when the contact with the trigger object is detected.
	void MySimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count) 
	{
		//you can read the trigger information here
		for (PxU32 i = 0; i < count; i++)
		{
			//filter out contact with the planes
			if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
			{
				//check if eNOTIFY_TOUCH_FOUND trigger
				if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					OutOfPlayCheck(pairs,i);

					if(pairs[i].otherShape->getGeometryType() == PxGeometryType::eSPHERE)
					{
						CheckMainBall(pairs, i);
						CheckMultiBalls(pairs,i);
						MultiBallLaunchCheck(pairs,i);
						
						if((scene->PinballTable->GetShapeColours()->GetColour(MIDDLEBUMPER) == scene->PinballTable->GetShapeColours()->GetColourAtIndex(4))
						& (scene->PinballTable->GetShapeColours()->GetColour(RIGHTBUMPER) == scene->PinballTable->GetShapeColours()->GetColourAtIndex(4))
						& (scene->PinballTable->GetShapeColours()->GetColour(LEFTBUMPER) == scene->PinballTable->GetShapeColours()->GetColourAtIndex(4))
						& !gameLogic->IsMultiball())
						{
							gameLogic->SetMultiball();
							multiBallActive = true;
							scene->multiBalls.at(0)->SetResetStatus(true);
						}
					}

					//cerr << "eNOTIFY_TOUCH_FOUND" << endl;
				}
				//check if eNOTIFY_TOUCH_LOST trigger
				if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					//cerr << "eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}
	}

	// check the main ball for collision with bumpers and updat scores
	void MySimulationEventCallback::CheckMainBall(PxTriggerPair* pairs, PxU32 i)
		{
			if(pairs[i].triggerShape->getActor() == scene->middleBumperTrigger->Get() 
							&& pairs[i].otherShape->getActor() == scene->ball->Get())
			{
				if(scene->PinballTable->GetShapeColours()->GetColour(MIDDLEBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(4))
				{
					gameLogic->IncreaseScore(400);
					scene->ballScore +=400;
				}
				else if(scene->PinballTable->GetShapeColours()->GetColour(MIDDLEBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(3))
				{
					gameLogic->IncreaseScore(200);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::MIDDLEBUMPER,4);
					scene->ballScore +=200;
				}
						
				else
				{
					gameLogic->IncreaseScore(100);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::MIDDLEBUMPER,3);
					scene->ballScore +=100;
				}
			}

			else if(pairs[i].triggerShape->getActor() == scene->leftBumperTrigger->Get() 
				&& pairs[i].otherShape->getActor() == scene->ball->Get())
			{
				if(scene->PinballTable->GetShapeColours()->GetColour(LEFTBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(4))
				{
					gameLogic->IncreaseScore(400);
					scene->ballScore +=400;
				}

				else if(scene->PinballTable->GetShapeColours()->GetColour(LEFTBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(3))
				{
					gameLogic->IncreaseScore(200);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::LEFTBUMPER,4);
					scene->ballScore +=200;
				}
						
				else
				{
					gameLogic->IncreaseScore(100);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::LEFTBUMPER,3);
						scene->ballScore +=100;
				}
			}
					
			else if(pairs[i].triggerShape->getActor() == scene->rightBumperTrigger->Get() 
				&& pairs[i].otherShape->getActor() == scene->ball->Get())
			{

				if(scene->PinballTable->GetShapeColours()->GetColour(RIGHTBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(4))
				{
					gameLogic->IncreaseScore(400);
					scene->ballScore +=400;
				}
				else if(scene->PinballTable->GetShapeColours()->GetColour(RIGHTBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(3))
				{
					gameLogic->IncreaseScore(200);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::RIGHTBUMPER,4);
					scene->ballScore +=200;
				}
						
				else
				{
					gameLogic->IncreaseScore(100);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::RIGHTBUMPER,3);
					scene->ballScore +=100;
				}
			}
		}

	//check for any balls being out of play
	void MySimulationEventCallback::OutOfPlayCheck(PxTriggerPair* pairs, PxU32 i)
	{
		if(pairs[i].triggerShape->getActor() == scene->bottomBound->Get() 
						&& pairs[i].otherShape->getActor() == scene->ball->Get())
					{
						if(gameLogic->GetLives() >= 1 && !ballOutOfBounds)
						{
							gameLogic->removeLife();
							if(gameLogic->GetLives() > 0)
							{
								// Set trigger for callback functtion to reset ball once multiball has finished
								ballOutOfBounds = true;								
							}
							else
							{
								cout << "Ball Lifetime: " << scene->lifeTime << endl;
								cout << "Ball score: " << scene->ballScore << endl;
								cout << "Final score: " << gameLogic->GetScore() << endl;
								gameLogic->GameOver();
							}
						}
						
					}
					for(unsigned int j = 0; j < scene->multiBalls.size(); j++)
					{
						if(pairs[i].triggerShape->getActor() == scene->bottomBound->Get() 
							&& pairs[i].otherShape->getActor() == scene->multiBalls.at(j)->Get())
						{
							scene->multiBalls.at(j)->SetInPlayStatus(false);
						}
					}

					//Reset multiball
					if(!scene->multiBalls.at(0)->GetInPlayStatus() && 
						scene->multiBalls.at(0)->GetLaunchedStatus() &&
						!scene->multiBalls.at(1)->GetInPlayStatus() &&
						scene->multiBalls.at(1)->GetLaunchedStatus() &&
						!scene->multiBalls.at(2)->GetInPlayStatus() &&
						scene->multiBalls.at(2)->GetLaunchedStatus() &&
						multiBallActive)
					{
						gameLogic->EndMultiball();
						multiBallActive = false;
						scene->PinballTable->GetShapeColours()->SetShapeColour(MIDDLEBUMPER,2);
						scene->PinballTable->GetShapeColours()->SetShapeColour(LEFTBUMPER,2);
						scene->PinballTable->GetShapeColours()->SetShapeColour(RIGHTBUMPER,2);
					}
	}

	//Check multiball collisions and update score accordingly
	void MySimulationEventCallback::CheckMultiBalls(PxTriggerPair* pairs, PxU32 i)
	{
		//Loop through each ball and check for a collision
		for(unsigned int j = 0; j < scene->multiBalls.size(); j++)
		{
			if((pairs[i].triggerShape->getActor() == scene->middleBumperTrigger->Get() 
				&& pairs[i].otherShape->getActor() == scene->multiBalls.at(j)->Get()))
			{
				if(scene->PinballTable->GetShapeColours()->GetColour(MIDDLEBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(4))
				{
					gameLogic->IncreaseScore(400);
					scene->ballScore +=400;
				}
				else if(scene->PinballTable->GetShapeColours()->GetColour(MIDDLEBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(3))
				{
					gameLogic->IncreaseScore(200);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::MIDDLEBUMPER,4);
					scene->ballScore +=200;
				}
						
				else
				{
					gameLogic->IncreaseScore(100);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::MIDDLEBUMPER,3);
					scene->ballScore +=100;
				}
			}
			if((pairs[i].triggerShape->getActor() == scene->leftBumperTrigger->Get() 
				&& pairs[i].otherShape->getActor() == scene->multiBalls.at(j)->Get()))
			{
				if(scene->PinballTable->GetShapeColours()->GetColour(LEFTBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(4))
				{
					gameLogic->IncreaseScore(400);
					scene->ballScore +=400;
				}
				else if(scene->PinballTable->GetShapeColours()->GetColour(LEFTBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(3))
				{
					gameLogic->IncreaseScore(200);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::LEFTBUMPER,4);
					scene->ballScore +=200;
				}
						
				else
				{
					gameLogic->IncreaseScore(100);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::LEFTBUMPER,3);
					scene->ballScore +=100;
				}
			}
			if((pairs[i].triggerShape->getActor() == scene->rightBumperTrigger->Get() 
				&& pairs[i].otherShape->getActor() == scene->multiBalls.at(j)->Get()))
			{
				if(scene->PinballTable->GetShapeColours()->GetColour(RIGHTBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(4))
				{
					gameLogic->IncreaseScore(400);
					scene->ballScore +=400;
				}
				else if(scene->PinballTable->GetShapeColours()->GetColour(RIGHTBUMPER) 
					== scene->PinballTable->GetShapeColours()->GetColourAtIndex(3))
				{
					gameLogic->IncreaseScore(200);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::RIGHTBUMPER,4);
					scene->ballScore +=200;
				}
						
				else
				{
					gameLogic->IncreaseScore(100);
					scene->PinballTable->GetShapeColours()->SetShapeColour(tableShapes::RIGHTBUMPER,3);
					scene->ballScore +=100;
				}
			}
		}
		
		}

	//Check for multi ball launches
	void MySimulationEventCallback::MultiBallLaunchCheck(PxTriggerPair* pairs, PxU32 i)
	{
		if((pairs[i].triggerShape->getActor() == scene->launchTrigger->Get() 
			&& pairs[i].otherShape->getActor() == scene->multiBalls.at(0)->Get())
			&& !scene->multiBalls.at(0)->GetInPlayStatus())
		{
			scene->multiBalls.at(0)->SetInPlayStatus(true);
			scene->multiBalls.at(0)->SetLaunchStatus(true);

			scene->multiBalls.at(1)->SetResetStatus(true);
		}
		if(pairs[i].triggerShape->getActor() == scene->launchTrigger->Get() 
			&& pairs[i].otherShape->getActor() == scene->multiBalls.at(1)->Get()
			&& !scene->multiBalls.at(1)->GetInPlayStatus())
		{
			scene->multiBalls.at(2)->SetResetStatus(true);
   			scene->multiBalls.at(1)->SetLaunchStatus(true);
			scene->multiBalls.at(1)->SetInPlayStatus(true);
			scene->multiBalls.at(2)->SetInPlayStatus(true);
		}

		if(pairs[i].triggerShape->getActor() == scene->launchTrigger->Get() 
			&& pairs[i].otherShape->getActor() == scene->multiBalls.at(2)->Get()
			&& scene->multiBalls.at(2)->GetInPlayStatus())
		{
			scene->multiBalls.at(2)->SetLaunchStatus(true);
		}
	}
}